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
typedef  int u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MII_TG3_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_TG3_DSP_CONTROL ; 
 int /*<<< orphan*/  MII_TG3_DSP_RW_PORT ; 
 scalar_t__ tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ tg3_wait_macro_done (struct tg3*) ; 
 int /*<<< orphan*/  tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int tg3_phy_write_and_check_testpat(struct tg3 *tp, int *resetp)
{
	static const u32 test_pat[4][6] = {
	{ 0x00005555, 0x00000005, 0x00002aaa, 0x0000000a, 0x00003456, 0x00000003 },
	{ 0x00002aaa, 0x0000000a, 0x00003333, 0x00000003, 0x0000789a, 0x00000005 },
	{ 0x00005a5a, 0x00000005, 0x00002a6a, 0x0000000a, 0x00001bcd, 0x00000003 },
	{ 0x00002a5a, 0x0000000a, 0x000033c3, 0x00000003, 0x00002ef1, 0x00000005 }
	};
	int chan;

	for (chan = 0; chan < 4; chan++) {
		int i;

		tg3_writephy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0002);

		for (i = 0; i < 6; i++)
			tg3_writephy(tp, MII_TG3_DSP_RW_PORT,
				     test_pat[chan][i]);

		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0202);
		if (tg3_wait_macro_done(tp)) {
			*resetp = 1;
			return -EBUSY;
		}

		tg3_writephy(tp, MII_TG3_DSP_ADDRESS,
			     (chan * 0x2000) | 0x0200);
		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0082);
		if (tg3_wait_macro_done(tp)) {
			*resetp = 1;
			return -EBUSY;
		}

		tg3_writephy(tp, MII_TG3_DSP_CONTROL, 0x0802);
		if (tg3_wait_macro_done(tp)) {
			*resetp = 1;
			return -EBUSY;
		}

		for (i = 0; i < 6; i += 2) {
			u32 low, high;

			if (tg3_readphy(tp, MII_TG3_DSP_RW_PORT, &low) ||
			    tg3_readphy(tp, MII_TG3_DSP_RW_PORT, &high) ||
			    tg3_wait_macro_done(tp)) {
				*resetp = 1;
				return -EBUSY;
			}
			low &= 0x7fff;
			high &= 0x000f;
			if (low != test_pat[chan][i] ||
			    high != test_pat[chan][i+1]) {
				tg3_writephy(tp, MII_TG3_DSP_ADDRESS, 0x000b);
				tg3_writephy(tp, MII_TG3_DSP_RW_PORT, 0x4001);
				tg3_writephy(tp, MII_TG3_DSP_RW_PORT, 0x4005);

				return -EBUSY;
			}
		}
	}

	return 0;
}