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
typedef  int u16 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_fn_config {scalar_t__ dvsec_afu_info_pos; } ;

/* Variables and functions */
 scalar_t__ OCXL_DVSEC_AFU_INFO_AFU_IDX ; 
 int OCXL_TEMPL_LEN_1_0 ; 
 int OCXL_TEMPL_LEN_1_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,int) ; 
 int read_template_version (struct pci_dev*,struct ocxl_fn_config*,int*,int*) ; 

int ocxl_config_check_afu_index(struct pci_dev *dev,
				struct ocxl_fn_config *fn, int afu_idx)
{
	int rc;
	u16 templ_version;
	u16 len, expected_len;

	pci_write_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXL_DVSEC_AFU_INFO_AFU_IDX,
			afu_idx);

	rc = read_template_version(dev, fn, &len, &templ_version);
	if (rc)
		return rc;

	/* AFU index map can have holes, in which case we read all 0's */
	if (!templ_version && !len)
		return 0;

	dev_dbg(&dev->dev, "AFU descriptor template version %d.%d\n",
		templ_version >> 8, templ_version & 0xFF);

	switch (templ_version) {
	case 0x0005: // v0.5 was used prior to the spec approval
	case 0x0100:
		expected_len = OCXL_TEMPL_LEN_1_0;
		break;
	case 0x0101:
		expected_len = OCXL_TEMPL_LEN_1_1;
		break;
	default:
		dev_warn(&dev->dev, "Unknown AFU template version %#x\n",
			templ_version);
		expected_len = len;
	}
	if (len != expected_len)
		dev_warn(&dev->dev,
			"Unexpected template length %#x in AFU information, expected %#x for version %#x\n",
			len, expected_len, templ_version);
	return 1;
}