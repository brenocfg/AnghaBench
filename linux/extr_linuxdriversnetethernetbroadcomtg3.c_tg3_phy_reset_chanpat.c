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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MII_TG3_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_TG3_DSP_CONTROL ; 
 int /*<<< orphan*/  MII_TG3_DSP_RW_PORT ; 
 scalar_t__ tg3_wait_macro_done (struct tg3*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_phy_reset_chanpat(struct tg3 *tp)
{
	int chan;

	for (chan = 0; chan < 4; chan++) {
		int i;

		tg3_writephy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0002);
		for (i = 0; i < 6; i++)
			tg3_writephy(tp, MII_TG3_DSP_RW_PORT, 0x000);
		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0202);
		if (tg3_wait_macro_done(tp))
			return -EBUSY;
	}

	return 0;
}