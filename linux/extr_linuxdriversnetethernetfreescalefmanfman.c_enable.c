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
typedef  int u32 ;
struct fman_cfg {int qmi_def_tnums_thresh; } ;
struct fman {TYPE_2__* qmi_regs; TYPE_1__* bmi_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmqm_gc; } ;
struct TYPE_3__ {int /*<<< orphan*/  fmbm_init; } ;

/* Variables and functions */
 int BMI_INIT_START ; 
 int QMI_CFG_DEQ_EN ; 
 int QMI_CFG_ENQ_EN ; 
 int QMI_CFG_EN_COUNTERS ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int enable(struct fman *fman, struct fman_cfg *cfg)
{
	u32 cfg_reg = 0;

	/* Enable all modules */

	/* clear&enable global counters - calculate reg and save for later,
	 * because it's the same reg for QMI enable
	 */
	cfg_reg = QMI_CFG_EN_COUNTERS;

	/* Set enqueue and dequeue thresholds */
	cfg_reg |= (cfg->qmi_def_tnums_thresh << 8) | cfg->qmi_def_tnums_thresh;

	iowrite32be(BMI_INIT_START, &fman->bmi_regs->fmbm_init);
	iowrite32be(cfg_reg | QMI_CFG_ENQ_EN | QMI_CFG_DEQ_EN,
		    &fman->qmi_regs->fmqm_gc);

	return 0;
}