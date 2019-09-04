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
typedef  int /*<<< orphan*/  u8 ;
struct rome_config {int /*<<< orphan*/  dnld_mode; int /*<<< orphan*/  fwname; } ;
struct hci_dev {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int MAX_SIZE_PER_TLV_SEGMENT ; 
 int /*<<< orphan*/  ROME_SKIP_EVT_NONE ; 
 int /*<<< orphan*/  bt_dev_dbg (struct hci_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  qca_tlv_check_data (struct rome_config*,struct firmware const*) ; 
 int qca_tlv_send_segment (struct hci_dev*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qca_download_firmware(struct hci_dev *hdev,
				  struct rome_config *config)
{
	const struct firmware *fw;
	const u8 *segment;
	int ret, remain, i = 0;

	bt_dev_info(hdev, "QCA Downloading %s", config->fwname);

	ret = request_firmware(&fw, config->fwname, &hdev->dev);
	if (ret) {
		bt_dev_err(hdev, "QCA Failed to request file: %s (%d)",
			   config->fwname, ret);
		return ret;
	}

	qca_tlv_check_data(config, fw);

	segment = fw->data;
	remain = fw->size;
	while (remain > 0) {
		int segsize = min(MAX_SIZE_PER_TLV_SEGMENT, remain);

		bt_dev_dbg(hdev, "Send segment %d, size %d", i++, segsize);

		remain -= segsize;
		/* The last segment is always acked regardless download mode */
		if (!remain || segsize < MAX_SIZE_PER_TLV_SEGMENT)
			config->dnld_mode = ROME_SKIP_EVT_NONE;

		ret = qca_tlv_send_segment(hdev, segsize, segment,
					    config->dnld_mode);
		if (ret)
			break;

		segment += segsize;
	}

	release_firmware(fw);

	return ret;
}