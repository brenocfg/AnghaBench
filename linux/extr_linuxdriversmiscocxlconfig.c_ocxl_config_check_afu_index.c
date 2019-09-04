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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct ocxl_fn_config {scalar_t__ dvsec_afu_info_pos; } ;

/* Variables and functions */
 int EXTRACT_BITS (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ OCXL_DVSEC_AFU_INFO_AFU_IDX ; 
 int /*<<< orphan*/  OCXL_DVSEC_TEMPL_VERSION ; 
 int OCXL_TEMPL_LEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,scalar_t__,int) ; 
 int read_afu_info (struct pci_dev*,struct ocxl_fn_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ocxl_config_check_afu_index(struct pci_dev *dev,
				struct ocxl_fn_config *fn, int afu_idx)
{
	u32 val;
	int rc, templ_major, templ_minor, len;

	pci_write_config_byte(dev,
			fn->dvsec_afu_info_pos + OCXL_DVSEC_AFU_INFO_AFU_IDX,
			afu_idx);
	rc = read_afu_info(dev, fn, OCXL_DVSEC_TEMPL_VERSION, &val);
	if (rc)
		return rc;

	/* AFU index map can have holes */
	if (!val)
		return 0;

	templ_major = EXTRACT_BITS(val, 8, 15);
	templ_minor = EXTRACT_BITS(val, 0, 7);
	dev_dbg(&dev->dev, "AFU descriptor template version %d.%d\n",
		templ_major, templ_minor);

	len = EXTRACT_BITS(val, 16, 31);
	if (len != OCXL_TEMPL_LEN) {
		dev_warn(&dev->dev,
			"Unexpected template length in AFU information (%#x)\n",
			len);
	}
	return 1;
}