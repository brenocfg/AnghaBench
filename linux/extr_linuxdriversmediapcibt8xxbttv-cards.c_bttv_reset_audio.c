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
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {int id; TYPE_1__ c; } ;

/* Variables and functions */
 scalar_t__ bttv_debug ; 
 int /*<<< orphan*/  btwrite (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bttv_reset_audio(struct bttv *btv)
{
	/*
	 * BT878A has a audio-reset register.
	 * 1. This register is an audio reset function but it is in
	 *    function-0 (video capture) address space.
	 * 2. It is enough to do this once per power-up of the card.
	 * 3. There is a typo in the Conexant doc -- it is not at
	 *    0x5B, but at 0x058. (B is an odd-number, obviously a typo!).
	 * --//Shrikumar 030609
	 */
	if (btv->id != 878)
		return;

	if (bttv_debug)
		pr_debug("%d: BT878A ARESET\n", btv->c.nr);
	btwrite((1<<7), 0x058);
	udelay(10);
	btwrite(     0, 0x058);
}