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
struct whcrc {scalar_t__ rc_base; int /*<<< orphan*/  event_work; struct umc_dev* umc_dev; } ;
struct uwb_rc {struct whcrc* priv; } ;
struct umc_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ URCCMD ; 
 scalar_t__ URCINTR ; 
 scalar_t__ URCSTS ; 
 int /*<<< orphan*/  URCSTS_HALTED ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  whci_wait_for (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static
void whcrc_stop_rc(struct uwb_rc *rc)
{
	struct whcrc *whcrc = rc->priv;
	struct umc_dev *umc_dev = whcrc->umc_dev;

	le_writel(0, whcrc->rc_base + URCINTR);
	cancel_work_sync(&whcrc->event_work);

	le_writel(0, whcrc->rc_base + URCCMD);
	whci_wait_for(&umc_dev->dev, whcrc->rc_base + URCSTS,
		      URCSTS_HALTED, URCSTS_HALTED, 100, "radio controller stop");
}