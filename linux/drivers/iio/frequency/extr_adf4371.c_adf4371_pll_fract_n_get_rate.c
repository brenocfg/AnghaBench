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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct adf4371_state {int fract1; int fpfd; int mod2; unsigned int rf_div_sel; scalar_t__ fract2; scalar_t__ integer; } ;

/* Variables and functions */
 scalar_t__ ADF4371_CH_RF16 ; 
 scalar_t__ ADF4371_CH_RF32 ; 
 scalar_t__ ADF4371_CH_RF8 ; 
 scalar_t__ ADF4371_CH_RFAUX8 ; 
 int ADF4371_MODULUS1 ; 
 int /*<<< orphan*/  do_div (unsigned long long,int) ; 

__attribute__((used)) static unsigned long long adf4371_pll_fract_n_get_rate(struct adf4371_state *st,
						       u32 channel)
{
	unsigned long long val, tmp;
	unsigned int ref_div_sel;

	val = (((u64)st->integer * ADF4371_MODULUS1) + st->fract1) * st->fpfd;
	tmp = (u64)st->fract2 * st->fpfd;
	do_div(tmp, st->mod2);
	val += tmp + ADF4371_MODULUS1 / 2;

	if (channel == ADF4371_CH_RF8 || channel == ADF4371_CH_RFAUX8)
		ref_div_sel = st->rf_div_sel;
	else
		ref_div_sel = 0;

	do_div(val, ADF4371_MODULUS1 * (1 << ref_div_sel));

	if (channel == ADF4371_CH_RF16)
		val <<= 1;
	else if (channel == ADF4371_CH_RF32)
		val <<= 2;

	return val;
}