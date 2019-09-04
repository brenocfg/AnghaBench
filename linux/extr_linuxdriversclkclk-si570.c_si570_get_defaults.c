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
typedef  long long u64 ;
struct clk_si570 {int rfreq; long long n1; long long hs_div; long long frequency; void* fxtal; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI570_CNTRL_RECALL ; 
 int /*<<< orphan*/  SI570_REG_CONTROL ; 
 void* div64_u64 (long long,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si570_get_divs (struct clk_si570*,int*,long long*,long long*) ; 

__attribute__((used)) static int si570_get_defaults(struct clk_si570 *data, u64 fout)
{
	int err;
	u64 fdco;

	regmap_write(data->regmap, SI570_REG_CONTROL, SI570_CNTRL_RECALL);

	err = si570_get_divs(data, &data->rfreq, &data->n1, &data->hs_div);
	if (err)
		return err;

	/*
	 * Accept optional precision loss to avoid arithmetic overflows.
	 * Acceptable per Silicon Labs Application Note AN334.
	 */
	fdco = fout * data->n1 * data->hs_div;
	if (fdco >= (1LL << 36))
		data->fxtal = div64_u64(fdco << 24, data->rfreq >> 4);
	else
		data->fxtal = div64_u64(fdco << 28, data->rfreq);

	data->frequency = fout;

	return 0;
}