#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfi1_devdata {TYPE_1__* pcidev; } ;
struct firmware_file {int /*<<< orphan*/  firmware; int /*<<< orphan*/  signature; int /*<<< orphan*/  exponent; int /*<<< orphan*/  modulus; } ;
struct TYPE_5__ {int /*<<< orphan*/  mu; int /*<<< orphan*/  r2; } ;
struct firmware_details {int firmware_len; TYPE_3__* fw; int /*<<< orphan*/  firmware_ptr; int /*<<< orphan*/  mu; int /*<<< orphan*/  r2; int /*<<< orphan*/  signature; int /*<<< orphan*/  exponent; int /*<<< orphan*/  modulus; struct css_header* css_header; TYPE_2__ dummy_header; } ;
struct css_header {int module_type; int header_len; int header_version; int module_id; int module_vendor; int date; int size; int key_size; int modulus_size; int exponent_size; } ;
struct augmented_firmware_file {int /*<<< orphan*/  firmware; int /*<<< orphan*/  mu; int /*<<< orphan*/  r2; int /*<<< orphan*/  signature; int /*<<< orphan*/  exponent; int /*<<< orphan*/  modulus; } ;
struct TYPE_6__ {int size; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AUGMENT_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIRMWARE ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,char const*) ; 
 int /*<<< orphan*/  dd_dev_warn (struct hfi1_devdata*,char*,char const*,int) ; 
 int /*<<< orphan*/  dispose_one_firmware (struct firmware_details*) ; 
 int /*<<< orphan*/  hfi1_cdbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct firmware_details*,int /*<<< orphan*/ ,int) ; 
 int payload_check (struct hfi1_devdata*,char const*,int,int) ; 
 int request_firmware (TYPE_3__**,char const*,int /*<<< orphan*/ *) ; 
 int verify_css_header (struct hfi1_devdata*,struct css_header*) ; 

__attribute__((used)) static int obtain_one_firmware(struct hfi1_devdata *dd, const char *name,
			       struct firmware_details *fdet)
{
	struct css_header *css;
	int ret;

	memset(fdet, 0, sizeof(*fdet));

	ret = request_firmware(&fdet->fw, name, &dd->pcidev->dev);
	if (ret) {
		dd_dev_warn(dd, "cannot find firmware \"%s\", err %d\n",
			    name, ret);
		return ret;
	}

	/* verify the firmware */
	if (fdet->fw->size < sizeof(struct css_header)) {
		dd_dev_err(dd, "firmware \"%s\" is too small\n", name);
		ret = -EINVAL;
		goto done;
	}
	css = (struct css_header *)fdet->fw->data;

	hfi1_cdbg(FIRMWARE, "Firmware %s details:", name);
	hfi1_cdbg(FIRMWARE, "file size: 0x%lx bytes", fdet->fw->size);
	hfi1_cdbg(FIRMWARE, "CSS structure:");
	hfi1_cdbg(FIRMWARE, "  module_type    0x%x", css->module_type);
	hfi1_cdbg(FIRMWARE, "  header_len     0x%03x (0x%03x bytes)",
		  css->header_len, 4 * css->header_len);
	hfi1_cdbg(FIRMWARE, "  header_version 0x%x", css->header_version);
	hfi1_cdbg(FIRMWARE, "  module_id      0x%x", css->module_id);
	hfi1_cdbg(FIRMWARE, "  module_vendor  0x%x", css->module_vendor);
	hfi1_cdbg(FIRMWARE, "  date           0x%x", css->date);
	hfi1_cdbg(FIRMWARE, "  size           0x%03x (0x%03x bytes)",
		  css->size, 4 * css->size);
	hfi1_cdbg(FIRMWARE, "  key_size       0x%03x (0x%03x bytes)",
		  css->key_size, 4 * css->key_size);
	hfi1_cdbg(FIRMWARE, "  modulus_size   0x%03x (0x%03x bytes)",
		  css->modulus_size, 4 * css->modulus_size);
	hfi1_cdbg(FIRMWARE, "  exponent_size  0x%03x (0x%03x bytes)",
		  css->exponent_size, 4 * css->exponent_size);
	hfi1_cdbg(FIRMWARE, "firmware size: 0x%lx bytes",
		  fdet->fw->size - sizeof(struct firmware_file));

	/*
	 * If the file does not have a valid CSS header, fail.
	 * Otherwise, check the CSS size field for an expected size.
	 * The augmented file has r2 and mu inserted after the header
	 * was generated, so there will be a known difference between
	 * the CSS header size and the actual file size.  Use this
	 * difference to identify an augmented file.
	 *
	 * Note: css->size is in DWORDs, multiply by 4 to get bytes.
	 */
	ret = verify_css_header(dd, css);
	if (ret) {
		dd_dev_info(dd, "Invalid CSS header for \"%s\"\n", name);
	} else if ((css->size * 4) == fdet->fw->size) {
		/* non-augmented firmware file */
		struct firmware_file *ff = (struct firmware_file *)
							fdet->fw->data;

		/* make sure there are bytes in the payload */
		ret = payload_check(dd, name, fdet->fw->size,
				    sizeof(struct firmware_file));
		if (ret == 0) {
			fdet->css_header = css;
			fdet->modulus = ff->modulus;
			fdet->exponent = ff->exponent;
			fdet->signature = ff->signature;
			fdet->r2 = fdet->dummy_header.r2; /* use dummy space */
			fdet->mu = fdet->dummy_header.mu; /* use dummy space */
			fdet->firmware_ptr = ff->firmware;
			fdet->firmware_len = fdet->fw->size -
						sizeof(struct firmware_file);
			/*
			 * Header does not include r2 and mu - generate here.
			 * For now, fail.
			 */
			dd_dev_err(dd, "driver is unable to validate firmware without r2 and mu (not in firmware file)\n");
			ret = -EINVAL;
		}
	} else if ((css->size * 4) + AUGMENT_SIZE == fdet->fw->size) {
		/* augmented firmware file */
		struct augmented_firmware_file *aff =
			(struct augmented_firmware_file *)fdet->fw->data;

		/* make sure there are bytes in the payload */
		ret = payload_check(dd, name, fdet->fw->size,
				    sizeof(struct augmented_firmware_file));
		if (ret == 0) {
			fdet->css_header = css;
			fdet->modulus = aff->modulus;
			fdet->exponent = aff->exponent;
			fdet->signature = aff->signature;
			fdet->r2 = aff->r2;
			fdet->mu = aff->mu;
			fdet->firmware_ptr = aff->firmware;
			fdet->firmware_len = fdet->fw->size -
					sizeof(struct augmented_firmware_file);
		}
	} else {
		/* css->size check failed */
		dd_dev_err(dd,
			   "invalid firmware header field size: expected 0x%lx or 0x%lx, actual 0x%x\n",
			   fdet->fw->size / 4,
			   (fdet->fw->size - AUGMENT_SIZE) / 4,
			   css->size);

		ret = -EINVAL;
	}

done:
	/* if returning an error, clean up after ourselves */
	if (ret)
		dispose_one_firmware(fdet);
	return ret;
}