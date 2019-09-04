#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;
struct ispccdc_lsc_config_req {TYPE_1__ table; int /*<<< orphan*/  config; int /*<<< orphan*/  enable; } ;
struct isp_ccdc_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 scalar_t__ ccdc_lsc_busy (struct isp_ccdc_device*) ; 
 int /*<<< orphan*/  ccdc_lsc_program_table (struct isp_ccdc_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccdc_lsc_setup_regs (struct isp_ccdc_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ ccdc_lsc_validate_config (struct isp_ccdc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_device (struct isp_ccdc_device*) ; 

__attribute__((used)) static int __ccdc_lsc_configure(struct isp_ccdc_device *ccdc,
				struct ispccdc_lsc_config_req *req)
{
	if (!req->enable)
		return -EINVAL;

	if (ccdc_lsc_validate_config(ccdc, &req->config) < 0) {
		dev_dbg(to_device(ccdc), "Discard LSC configuration\n");
		return -EINVAL;
	}

	if (ccdc_lsc_busy(ccdc))
		return -EBUSY;

	ccdc_lsc_setup_regs(ccdc, &req->config);
	ccdc_lsc_program_table(ccdc, req->table.dma);
	return 0;
}