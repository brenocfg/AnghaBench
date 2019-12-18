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
struct TYPE_2__ {int /*<<< orphan*/  code; } ;
struct xsdfec_dev {TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  XSDFEC_FEC_CODE_ADDR ; 
 int /*<<< orphan*/  update_config_from_hw (struct xsdfec_dev*) ; 
 int /*<<< orphan*/  xsdfec_cfg_axi_streams (struct xsdfec_dev*) ; 
 int /*<<< orphan*/  xsdfec_regwrite (struct xsdfec_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xsdfec_set_default_config(struct xsdfec_dev *xsdfec)
{
	/* Ensure registers are aligned with core configuration */
	xsdfec_regwrite(xsdfec, XSDFEC_FEC_CODE_ADDR, xsdfec->config.code);
	xsdfec_cfg_axi_streams(xsdfec);
	update_config_from_hw(xsdfec);

	return 0;
}