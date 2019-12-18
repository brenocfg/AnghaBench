#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_3__ {size_t lockstate; size_t slockstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  chg_vc_kbd_slock (TYPE_1__*,unsigned char) ; 
 int /*<<< orphan*/  k_shift (struct vc_data*,unsigned char,char) ; 
 TYPE_1__* kbd ; 
 int /*<<< orphan*/ * key_maps ; 
 scalar_t__ rep ; 

__attribute__((used)) static void k_slock(struct vc_data *vc, unsigned char value, char up_flag)
{
	k_shift(vc, value, up_flag);
	if (up_flag || rep)
		return;

	chg_vc_kbd_slock(kbd, value);
	/* try to make Alt, oops, AltGr and such work */
	if (!key_maps[kbd->lockstate ^ kbd->slockstate]) {
		kbd->slockstate = 0;
		chg_vc_kbd_slock(kbd, value);
	}
}