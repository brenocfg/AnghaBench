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
struct adf4350_state {int fpfd; int clkin; struct adf4350_platform_data* pdata; } ;
struct adf4350_platform_data {scalar_t__ ref_div2_en; scalar_t__ ref_doubler_en; } ;

/* Variables and functions */
 int ADF4350_MAX_FREQ_PFD ; 

__attribute__((used)) static int adf4350_tune_r_cnt(struct adf4350_state *st, unsigned short r_cnt)
{
	struct adf4350_platform_data *pdata = st->pdata;

	do {
		r_cnt++;
		st->fpfd = (st->clkin * (pdata->ref_doubler_en ? 2 : 1)) /
			   (r_cnt * (pdata->ref_div2_en ? 2 : 1));
	} while (st->fpfd > ADF4350_MAX_FREQ_PFD);

	return r_cnt;
}