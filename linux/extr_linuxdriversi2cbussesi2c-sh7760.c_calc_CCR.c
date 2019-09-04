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
struct clk {unsigned long rate; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 unsigned long abs (unsigned long) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 

__attribute__((used)) static int calc_CCR(unsigned long scl_hz)
{
	struct clk *mclk;
	unsigned long mck, m1, dff, odff, iclk;
	signed char cdf, cdfm;
	int scgd, scgdm, scgds;

	mclk = clk_get(NULL, "peripheral_clk");
	if (IS_ERR(mclk)) {
		return PTR_ERR(mclk);
	} else {
		mck = mclk->rate;
		clk_put(mclk);
	}

	odff = scl_hz;
	scgdm = cdfm = m1 = 0;
	for (cdf = 3; cdf >= 0; cdf--) {
		iclk = mck / (1 + cdf);
		if (iclk >= 20000000)
			continue;
		scgds = ((iclk / scl_hz) - 20) >> 3;
		for (scgd = scgds; (scgd < 63) && scgd <= scgds + 1; scgd++) {
			m1 = iclk / (20 + (scgd << 3));
			dff = abs(scl_hz - m1);
			if (dff < odff) {
				odff = dff;
				cdfm = cdf;
				scgdm = scgd;
			}
		}
	}
	/* fail if more than 25% off of requested SCL */
	if (odff > (scl_hz >> 2))
		return -EINVAL;

	/* create a CCR register value */
	return ((scgdm << 2) | cdfm);
}