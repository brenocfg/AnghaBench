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
struct TYPE_5__ {int pll_ofreq; } ;
struct TYPE_4__ {int /*<<< orphan*/  nr; } ;
struct bttv {size_t tvnorm; scalar_t__ input; scalar_t__ dig; TYPE_2__ pll; TYPE_1__ c; } ;
struct TYPE_6__ {int sram; int Fsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DVSIF ; 
 int /*<<< orphan*/  BT848_TGCTRL ; 
 int /*<<< orphan*/  BT848_TGLB ; 
 int** SRAM_Table ; 
 TYPE_3__* bttv_tvnorms ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pll (struct bttv*) ; 

__attribute__((used)) static void bt848A_set_timing(struct bttv *btv)
{
	int i, len;
	int table_idx = bttv_tvnorms[btv->tvnorm].sram;
	int fsc       = bttv_tvnorms[btv->tvnorm].Fsc;

	if (btv->input == btv->dig) {
		dprintk("%d: load digital timing table (table_idx=%d)\n",
			btv->c.nr,table_idx);

		/* timing change...reset timing generator address */
		btwrite(0x00, BT848_TGCTRL);
		btwrite(0x02, BT848_TGCTRL);
		btwrite(0x00, BT848_TGCTRL);

		len=SRAM_Table[table_idx][0];
		for(i = 1; i <= len; i++)
			btwrite(SRAM_Table[table_idx][i],BT848_TGLB);
		btv->pll.pll_ofreq = 27000000;

		set_pll(btv);
		btwrite(0x11, BT848_TGCTRL);
		btwrite(0x41, BT848_DVSIF);
	} else {
		btv->pll.pll_ofreq = fsc;
		set_pll(btv);
		btwrite(0x0, BT848_DVSIF);
	}
}