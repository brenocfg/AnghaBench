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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bna {TYPE_1__ ioceth; } ;

/* Variables and functions */
 scalar_t__ BNA_IS_ERR_INTR (struct bna*,int /*<<< orphan*/ ) ; 
 scalar_t__ BNA_IS_MBOX_INTR (struct bna*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_nw_ioc_mbox_isr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bna_err_handler (struct bna*,int /*<<< orphan*/ ) ; 

void
bna_mbox_handler(struct bna *bna, u32 intr_status)
{
	if (BNA_IS_ERR_INTR(bna, intr_status)) {
		bna_err_handler(bna, intr_status);
		return;
	}
	if (BNA_IS_MBOX_INTR(bna, intr_status))
		bfa_nw_ioc_mbox_isr(&bna->ioceth.ioc);
}