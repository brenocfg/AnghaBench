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
typedef  scalar_t__ u32 ;
struct smscore_device_t {int device_flags; int gfp_buf_flags; int /*<<< orphan*/  context; int /*<<< orphan*/  device; } ;
struct sms_firmware {int dummy; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
typedef  int (* loadfirmware_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SMS_ALLOC_ALIGNMENT ; 
 int SMS_DEVICE_FAMILY2 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 char* smscore_get_fw_filename (struct smscore_device_t*,int) ; 
 int smscore_load_firmware_family2 (struct smscore_device_t*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int smscore_load_firmware_from_file(struct smscore_device_t *coredev,
					   int mode,
					   loadfirmware_t loadfirmware_handler)
{
	int rc = -ENOENT;
	u8 *fw_buf;
	u32 fw_buf_size;
	const struct firmware *fw;

	char *fw_filename = smscore_get_fw_filename(coredev, mode);
	if (!fw_filename) {
		pr_err("mode %d not supported on this device\n", mode);
		return -ENOENT;
	}
	pr_debug("Firmware name: %s\n", fw_filename);

	if (!loadfirmware_handler &&
	    !(coredev->device_flags & SMS_DEVICE_FAMILY2))
		return -EINVAL;

	rc = request_firmware(&fw, fw_filename, coredev->device);
	if (rc < 0) {
		pr_err("failed to open firmware file '%s'\n", fw_filename);
		return rc;
	}
	pr_debug("read fw %s, buffer size=0x%zx\n", fw_filename, fw->size);
	fw_buf = kmalloc(ALIGN(fw->size + sizeof(struct sms_firmware),
			 SMS_ALLOC_ALIGNMENT), GFP_KERNEL | coredev->gfp_buf_flags);
	if (!fw_buf) {
		pr_err("failed to allocate firmware buffer\n");
		rc = -ENOMEM;
	} else {
		memcpy(fw_buf, fw->data, fw->size);
		fw_buf_size = fw->size;

		rc = (coredev->device_flags & SMS_DEVICE_FAMILY2) ?
			smscore_load_firmware_family2(coredev, fw_buf, fw_buf_size)
			: loadfirmware_handler(coredev->context, fw_buf,
			fw_buf_size);
	}

	kfree(fw_buf);
	release_firmware(fw);

	return rc;
}