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
typedef  int u16 ;
struct intelfb_info {int /*<<< orphan*/  int_lock; TYPE_3__* info; int /*<<< orphan*/  irq_flags; TYPE_1__* pdev; } ;
struct TYPE_5__ {int vmode; } ;
struct TYPE_6__ {TYPE_2__ var; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,int) ; 
 int EINVAL ; 
 int FB_VMODE_INTERLACED ; 
 int /*<<< orphan*/  HWSTAM ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IMR ; 
 int INREG16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  OUTREG16 (int /*<<< orphan*/ ,int) ; 
 int PIPE_A_EVENT_INTERRUPT ; 
 int VSYNC_PIPE_A_INTERRUPT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intelfbhw_irq ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct intelfb_info*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int intelfbhw_enable_irq(struct intelfb_info *dinfo)
{
	u16 tmp;
	if (!test_and_set_bit(0, &dinfo->irq_flags)) {
		if (request_irq(dinfo->pdev->irq, intelfbhw_irq, IRQF_SHARED,
				"intelfb", dinfo)) {
			clear_bit(0, &dinfo->irq_flags);
			return -EINVAL;
		}

		spin_lock_irq(&dinfo->int_lock);
		OUTREG16(HWSTAM, 0xfffe); /* i830 DRM uses ffff */
		OUTREG16(IMR, 0);
	} else
		spin_lock_irq(&dinfo->int_lock);

	if (dinfo->info->var.vmode & FB_VMODE_INTERLACED)
		tmp = PIPE_A_EVENT_INTERRUPT;
	else
		tmp = VSYNC_PIPE_A_INTERRUPT; /* non-interlaced */
	if (tmp != INREG16(IER)) {
		DBG_MSG("changing IER to 0x%X\n", tmp);
		OUTREG16(IER, tmp);
	}

	spin_unlock_irq(&dinfo->int_lock);
	return 0;
}