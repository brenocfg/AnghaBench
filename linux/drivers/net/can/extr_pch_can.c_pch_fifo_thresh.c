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
struct pch_can_priv {TYPE_2__* regs; } ;
struct TYPE_4__ {TYPE_1__* ifregs; } ;
struct TYPE_3__ {int /*<<< orphan*/  creq; int /*<<< orphan*/  mcont; int /*<<< orphan*/  id2; int /*<<< orphan*/  cmask; } ;

/* Variables and functions */
 int PCH_CMASK_ARB ; 
 int PCH_CMASK_CTRL ; 
 int PCH_CMASK_RDWR ; 
 int PCH_FIFO_THRESH ; 
 int /*<<< orphan*/  PCH_ID2_DIR ; 
 int /*<<< orphan*/  PCH_IF_MCONT_INTPND ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_can_bit_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_can_int_clr (struct pch_can_priv*,int) ; 
 int /*<<< orphan*/  pch_can_rw_msg_obj (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pch_fifo_thresh(struct pch_can_priv *priv, int obj_id)
{
	if (obj_id < PCH_FIFO_THRESH) {
		iowrite32(PCH_CMASK_RDWR | PCH_CMASK_CTRL |
			  PCH_CMASK_ARB, &priv->regs->ifregs[0].cmask);

		/* Clearing the Dir bit. */
		pch_can_bit_clear(&priv->regs->ifregs[0].id2, PCH_ID2_DIR);

		/* Clearing NewDat & IntPnd */
		pch_can_bit_clear(&priv->regs->ifregs[0].mcont,
				  PCH_IF_MCONT_INTPND);
		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, obj_id);
	} else if (obj_id > PCH_FIFO_THRESH) {
		pch_can_int_clr(priv, obj_id);
	} else if (obj_id == PCH_FIFO_THRESH) {
		int cnt;
		for (cnt = 0; cnt < PCH_FIFO_THRESH; cnt++)
			pch_can_int_clr(priv, cnt + 1);
	}
}