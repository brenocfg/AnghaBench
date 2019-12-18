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
struct sm501_devdata {int rev; } ;
struct sm501_clock {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  SM501_CLOCK_M1XCLK 131 
#define  SM501_CLOCK_MCLK 130 
#define  SM501_CLOCK_P2XCLK 129 
#define  SM501_CLOCK_V2XCLK 128 
 struct sm501_devdata* dev_get_drvdata (struct device*) ; 
 int sm501_calc_pll (int,struct sm501_clock*,int) ; 
 int sm501_select_clock (unsigned long,struct sm501_clock*,int) ; 

unsigned long sm501_find_clock(struct device *dev,
			       int clksrc,
			       unsigned long req_freq)
{
	struct sm501_devdata *sm = dev_get_drvdata(dev);
	unsigned long sm501_freq; /* the frequency achieveable by the 501 */
	struct sm501_clock to;

	switch (clksrc) {
	case SM501_CLOCK_P2XCLK:
		if (sm->rev >= 0xC0) {
			/* SM502 -> use the programmable PLL */
			sm501_freq = (sm501_calc_pll(2 * req_freq,
						     &to, 5) / 2);
		} else {
			sm501_freq = (sm501_select_clock(2 * req_freq,
							 &to, 5) / 2);
		}
		break;

	case SM501_CLOCK_V2XCLK:
		sm501_freq = (sm501_select_clock(2 * req_freq, &to, 3) / 2);
		break;

	case SM501_CLOCK_MCLK:
	case SM501_CLOCK_M1XCLK:
		sm501_freq = sm501_select_clock(req_freq, &to, 3);
		break;

	default:
		sm501_freq = 0;		/* error */
	}

	return sm501_freq;
}