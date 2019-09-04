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
typedef  int u8 ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;
struct hscx_hw {TYPE_1__ bch; TYPE_2__* ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPAC_STARB ; 
 int ReadHSCX (struct hscx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
waitforCEC(struct hscx_hw *hx)
{
	u8 starb, to = 50;

	while (to) {
		starb = ReadHSCX(hx, IPAC_STARB);
		if (!(starb & 0x04))
			break;
		udelay(1);
		to--;
	}
	if (to < 50)
		pr_debug("%s: B%1d CEC %d us\n", hx->ip->name, hx->bch.nr,
			 50 - to);
	if (!to)
		pr_info("%s: B%1d CEC timeout\n", hx->ip->name, hx->bch.nr);
}