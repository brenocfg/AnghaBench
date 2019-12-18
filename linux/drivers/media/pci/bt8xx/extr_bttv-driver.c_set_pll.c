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
struct TYPE_4__ {int pll_ofreq; int pll_current; scalar_t__ pll_ifreq; int /*<<< orphan*/  pll_crystal; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct bttv {TYPE_2__ pll; TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DSTATUS ; 
 int BT848_DSTATUS_PLOCK ; 
 int /*<<< orphan*/  BT848_PLL_XCI ; 
 int /*<<< orphan*/  BT848_TGCTRL ; 
 int btread (int /*<<< orphan*/ ) ; 
 scalar_t__ bttv_verbose ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  set_pll_freq (struct bttv*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void set_pll(struct bttv *btv)
{
	int i;

	if (!btv->pll.pll_crystal)
		return;

	if (btv->pll.pll_ofreq == btv->pll.pll_current) {
		dprintk("%d: PLL: no change required\n", btv->c.nr);
		return;
	}

	if (btv->pll.pll_ifreq == btv->pll.pll_ofreq) {
		/* no PLL needed */
		if (btv->pll.pll_current == 0)
			return;
		if (bttv_verbose)
			pr_info("%d: PLL can sleep, using XTAL (%d)\n",
				btv->c.nr, btv->pll.pll_ifreq);
		btwrite(0x00,BT848_TGCTRL);
		btwrite(0x00,BT848_PLL_XCI);
		btv->pll.pll_current = 0;
		return;
	}

	if (bttv_verbose)
		pr_info("%d: Setting PLL: %d => %d (needs up to 100ms)\n",
			btv->c.nr,
			btv->pll.pll_ifreq, btv->pll.pll_ofreq);
	set_pll_freq(btv, btv->pll.pll_ifreq, btv->pll.pll_ofreq);

	for (i=0; i<10; i++) {
		/*  Let other people run while the PLL stabilizes */
		msleep(10);

		if (btread(BT848_DSTATUS) & BT848_DSTATUS_PLOCK) {
			btwrite(0,BT848_DSTATUS);
		} else {
			btwrite(0x08,BT848_TGCTRL);
			btv->pll.pll_current = btv->pll.pll_ofreq;
			if (bttv_verbose)
				pr_info("PLL set ok\n");
			return;
		}
	}
	btv->pll.pll_current = -1;
	if (bttv_verbose)
		pr_info("Setting PLL failed\n");
	return;
}