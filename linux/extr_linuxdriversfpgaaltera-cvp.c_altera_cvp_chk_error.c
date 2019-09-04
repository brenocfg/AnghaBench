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
typedef  int u32 ;
struct fpga_manager {int /*<<< orphan*/  dev; struct altera_cvp_conf* priv; } ;
struct altera_cvp_conf {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  VSE_CVP_STATUS ; 
 int VSE_CVP_STATUS_CFG_ERR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static inline int altera_cvp_chk_error(struct fpga_manager *mgr, size_t bytes)
{
	struct altera_cvp_conf *conf = mgr->priv;
	u32 val;

	/* STEP 10 (optional) - check CVP_CONFIG_ERROR flag */
	pci_read_config_dword(conf->pci_dev, VSE_CVP_STATUS, &val);
	if (val & VSE_CVP_STATUS_CFG_ERR) {
		dev_err(&mgr->dev, "CVP_CONFIG_ERROR after %zu bytes!\n",
			bytes);
		return -EPROTO;
	}
	return 0;
}