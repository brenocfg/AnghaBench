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
typedef  int u64 ;
typedef  int u32 ;
struct brcms_c_info {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  d11core; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  brcms_c_time_lock (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_time_unlock (struct brcms_c_info*) ; 
 int /*<<< orphan*/  tsf_timerhigh ; 
 int /*<<< orphan*/  tsf_timerlow ; 

void brcms_c_tsf_set(struct brcms_c_info *wlc, u64 tsf)
{
	u32 tsf_h, tsf_l;

	brcms_c_time_lock(wlc);

	tsf_l = tsf;
	tsf_h = (tsf >> 32);

	/* read the tsf timer low, then high to get an atomic read */
	bcma_write32(wlc->hw->d11core, D11REGOFFS(tsf_timerlow), tsf_l);
	bcma_write32(wlc->hw->d11core, D11REGOFFS(tsf_timerhigh), tsf_h);

	brcms_c_time_unlock(wlc);
}