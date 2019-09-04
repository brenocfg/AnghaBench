#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* cs_context; int /*<<< orphan*/  prefetch_control; int /*<<< orphan*/  prefetch_config2; int /*<<< orphan*/  prefetch_config1; int /*<<< orphan*/  config; int /*<<< orphan*/  timeout_ctrl; int /*<<< orphan*/  irqenable; int /*<<< orphan*/  sysconfig; } ;
struct TYPE_3__ {int /*<<< orphan*/  config7; int /*<<< orphan*/  config6; int /*<<< orphan*/  config5; int /*<<< orphan*/  config4; int /*<<< orphan*/  config3; int /*<<< orphan*/  config2; int /*<<< orphan*/  config1; scalar_t__ is_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPMC_CONFIG ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG1 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG2 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG3 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG4 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG5 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG6 ; 
 int /*<<< orphan*/  GPMC_CS_CONFIG7 ; 
 int /*<<< orphan*/  GPMC_IRQENABLE ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONFIG1 ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONFIG2 ; 
 int /*<<< orphan*/  GPMC_PREFETCH_CONTROL ; 
 int /*<<< orphan*/  GPMC_SYSCONFIG ; 
 int /*<<< orphan*/  GPMC_TIMEOUT_CONTROL ; 
 int /*<<< orphan*/  gpmc_base ; 
 TYPE_2__ gpmc_context ; 
 int gpmc_cs_num ; 
 int /*<<< orphan*/  gpmc_cs_write_reg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpmc_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3_gpmc_restore_context(void)
{
	int i;

	if (!gpmc_base)
		return;

	gpmc_write_reg(GPMC_SYSCONFIG, gpmc_context.sysconfig);
	gpmc_write_reg(GPMC_IRQENABLE, gpmc_context.irqenable);
	gpmc_write_reg(GPMC_TIMEOUT_CONTROL, gpmc_context.timeout_ctrl);
	gpmc_write_reg(GPMC_CONFIG, gpmc_context.config);
	gpmc_write_reg(GPMC_PREFETCH_CONFIG1, gpmc_context.prefetch_config1);
	gpmc_write_reg(GPMC_PREFETCH_CONFIG2, gpmc_context.prefetch_config2);
	gpmc_write_reg(GPMC_PREFETCH_CONTROL, gpmc_context.prefetch_control);
	for (i = 0; i < gpmc_cs_num; i++) {
		if (gpmc_context.cs_context[i].is_valid) {
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG1,
				gpmc_context.cs_context[i].config1);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG2,
				gpmc_context.cs_context[i].config2);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG3,
				gpmc_context.cs_context[i].config3);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG4,
				gpmc_context.cs_context[i].config4);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG5,
				gpmc_context.cs_context[i].config5);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG6,
				gpmc_context.cs_context[i].config6);
			gpmc_cs_write_reg(i, GPMC_CS_CONFIG7,
				gpmc_context.cs_context[i].config7);
		}
	}
}