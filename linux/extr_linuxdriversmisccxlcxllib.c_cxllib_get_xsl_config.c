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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_dev {int dummy; } ;
struct cxllib_xsl_config {scalar_t__ dra; int /*<<< orphan*/  bar_addr; int /*<<< orphan*/  log_bar_size; int /*<<< orphan*/  version; int /*<<< orphan*/  dsnctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_HVMODE ; 
 int /*<<< orphan*/  CXL_CAPI_WINDOW_LOG_SIZE ; 
 int /*<<< orphan*/  CXL_CAPI_WINDOW_START ; 
 scalar_t__ CXL_INVALID_DRA ; 
 int /*<<< orphan*/  CXL_XSL_CONFIG_CURRENT_VERSION ; 
 int EINVAL ; 
 int allocate_dummy_read_buf () ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 
 int cxl_calc_capp_routing (struct pci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cxl_get_xsl9_dsnctl (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dra_mutex ; 
 scalar_t__ dummy_read_addr ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cxllib_get_xsl_config(struct pci_dev *dev, struct cxllib_xsl_config *cfg)
{
	int rc;
	u32 phb_index;
	u64 chip_id, capp_unit_id;

	if (!cpu_has_feature(CPU_FTR_HVMODE))
		return -EINVAL;

	mutex_lock(&dra_mutex);
	if (dummy_read_addr == CXL_INVALID_DRA) {
		rc = allocate_dummy_read_buf();
		if (rc) {
			mutex_unlock(&dra_mutex);
			return rc;
		}
	}
	mutex_unlock(&dra_mutex);

	rc = cxl_calc_capp_routing(dev, &chip_id, &phb_index, &capp_unit_id);
	if (rc)
		return rc;

	rc = cxl_get_xsl9_dsnctl(dev, capp_unit_id, &cfg->dsnctl);
	if (rc)
		return rc;

	cfg->version  = CXL_XSL_CONFIG_CURRENT_VERSION;
	cfg->log_bar_size = CXL_CAPI_WINDOW_LOG_SIZE;
	cfg->bar_addr = CXL_CAPI_WINDOW_START;
	cfg->dra = dummy_read_addr;
	return 0;
}