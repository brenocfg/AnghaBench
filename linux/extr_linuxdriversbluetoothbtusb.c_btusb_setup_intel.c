#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct sk_buff {int dummy; } ;
struct intel_version {scalar_t__ fw_patch_num; int /*<<< orphan*/  fw_build_yy; int /*<<< orphan*/  fw_build_ww; int /*<<< orphan*/  fw_build_num; int /*<<< orphan*/  fw_revision; int /*<<< orphan*/  fw_variant; int /*<<< orphan*/  hw_revision; int /*<<< orphan*/  hw_variant; int /*<<< orphan*/  hw_platform; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct firmware {int size; int /*<<< orphan*/  const* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_OP_RESET ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  btintel_check_bdaddr (struct hci_dev*) ; 
 int btintel_enter_mfg (struct hci_dev*) ; 
 int btintel_exit_mfg (struct hci_dev*,int,int) ; 
 int btintel_read_version (struct hci_dev*,struct intel_version*) ; 
 int /*<<< orphan*/  btintel_set_event_mask_mfg (struct hci_dev*,int) ; 
 struct firmware* btusb_setup_intel_get_fw (struct hci_dev*,struct intel_version*) ; 
 int btusb_setup_intel_patching (struct hci_dev*,struct firmware const*,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static int btusb_setup_intel(struct hci_dev *hdev)
{
	struct sk_buff *skb;
	const struct firmware *fw;
	const u8 *fw_ptr;
	int disable_patch, err;
	struct intel_version ver;

	BT_DBG("%s", hdev->name);

	/* The controller has a bug with the first HCI command sent to it
	 * returning number of completed commands as zero. This would stall the
	 * command processing in the Bluetooth core.
	 *
	 * As a workaround, send HCI Reset command first which will reset the
	 * number of completed commands and allow normal command processing
	 * from now on.
	 */
	skb = __hci_cmd_sync(hdev, HCI_OP_RESET, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		bt_dev_err(hdev, "sending initial HCI reset command failed (%ld)",
			   PTR_ERR(skb));
		return PTR_ERR(skb);
	}
	kfree_skb(skb);

	/* Read Intel specific controller version first to allow selection of
	 * which firmware file to load.
	 *
	 * The returned information are hardware variant and revision plus
	 * firmware variant, revision and build number.
	 */
	err = btintel_read_version(hdev, &ver);
	if (err)
		return err;

	bt_dev_info(hdev, "read Intel version: %02x%02x%02x%02x%02x%02x%02x%02x%02x",
		    ver.hw_platform, ver.hw_variant, ver.hw_revision,
		    ver.fw_variant,  ver.fw_revision, ver.fw_build_num,
		    ver.fw_build_ww, ver.fw_build_yy, ver.fw_patch_num);

	/* fw_patch_num indicates the version of patch the device currently
	 * have. If there is no patch data in the device, it is always 0x00.
	 * So, if it is other than 0x00, no need to patch the device again.
	 */
	if (ver.fw_patch_num) {
		bt_dev_info(hdev, "Intel device is already patched. "
			    "patch num: %02x", ver.fw_patch_num);
		goto complete;
	}

	/* Opens the firmware patch file based on the firmware version read
	 * from the controller. If it fails to open the matching firmware
	 * patch file, it tries to open the default firmware patch file.
	 * If no patch file is found, allow the device to operate without
	 * a patch.
	 */
	fw = btusb_setup_intel_get_fw(hdev, &ver);
	if (!fw)
		goto complete;
	fw_ptr = fw->data;

	/* Enable the manufacturer mode of the controller.
	 * Only while this mode is enabled, the driver can download the
	 * firmware patch data and configuration parameters.
	 */
	err = btintel_enter_mfg(hdev);
	if (err) {
		release_firmware(fw);
		return err;
	}

	disable_patch = 1;

	/* The firmware data file consists of list of Intel specific HCI
	 * commands and its expected events. The first byte indicates the
	 * type of the message, either HCI command or HCI event.
	 *
	 * It reads the command and its expected event from the firmware file,
	 * and send to the controller. Once __hci_cmd_sync_ev() returns,
	 * the returned event is compared with the event read from the firmware
	 * file and it will continue until all the messages are downloaded to
	 * the controller.
	 *
	 * Once the firmware patching is completed successfully,
	 * the manufacturer mode is disabled with reset and activating the
	 * downloaded patch.
	 *
	 * If the firmware patching fails, the manufacturer mode is
	 * disabled with reset and deactivating the patch.
	 *
	 * If the default patch file is used, no reset is done when disabling
	 * the manufacturer.
	 */
	while (fw->size > fw_ptr - fw->data) {
		int ret;

		ret = btusb_setup_intel_patching(hdev, fw, &fw_ptr,
						 &disable_patch);
		if (ret < 0)
			goto exit_mfg_deactivate;
	}

	release_firmware(fw);

	if (disable_patch)
		goto exit_mfg_disable;

	/* Patching completed successfully and disable the manufacturer mode
	 * with reset and activate the downloaded firmware patches.
	 */
	err = btintel_exit_mfg(hdev, true, true);
	if (err)
		return err;

	bt_dev_info(hdev, "Intel firmware patch completed and activated");

	goto complete;

exit_mfg_disable:
	/* Disable the manufacturer mode without reset */
	err = btintel_exit_mfg(hdev, false, false);
	if (err)
		return err;

	bt_dev_info(hdev, "Intel firmware patch completed");

	goto complete;

exit_mfg_deactivate:
	release_firmware(fw);

	/* Patching failed. Disable the manufacturer mode with reset and
	 * deactivate the downloaded firmware patches.
	 */
	err = btintel_exit_mfg(hdev, true, false);
	if (err)
		return err;

	bt_dev_info(hdev, "Intel firmware patch completed and deactivated");

complete:
	/* Set the event mask for Intel specific vendor events. This enables
	 * a few extra events that are useful during general operation.
	 */
	btintel_set_event_mask_mfg(hdev, false);

	btintel_check_bdaddr(hdev);
	return 0;
}