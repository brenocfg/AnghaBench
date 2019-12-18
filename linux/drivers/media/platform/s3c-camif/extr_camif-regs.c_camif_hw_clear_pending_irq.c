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
struct camif_vp {int /*<<< orphan*/  camif; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIGCTRL_IRQ_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIGCTRL ; 
 int /*<<< orphan*/  camif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void camif_hw_clear_pending_irq(struct camif_vp *vp)
{
	u32 cfg = camif_read(vp->camif, S3C_CAMIF_REG_CIGCTRL);
	cfg |= CIGCTRL_IRQ_CLR(vp->id);
	camif_write(vp->camif, S3C_CAMIF_REG_CIGCTRL, cfg);
}