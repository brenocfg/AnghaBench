#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {unsigned long long crtc_clock; } ;
struct TYPE_4__ {TYPE_1__ adjusted_mode; int /*<<< orphan*/  active; } ;
struct komeda_crtc_state {int /*<<< orphan*/  clock_ratio; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  div64_u64 (int,int) ; 
 int komeda_crtc_get_aclk (struct komeda_crtc_state*) ; 

__attribute__((used)) static void komeda_crtc_update_clock_ratio(struct komeda_crtc_state *kcrtc_st)
{
	u64 pxlclk, aclk;

	if (!kcrtc_st->base.active) {
		kcrtc_st->clock_ratio = 0;
		return;
	}

	pxlclk = kcrtc_st->base.adjusted_mode.crtc_clock * 1000ULL;
	aclk = komeda_crtc_get_aclk(kcrtc_st);

	kcrtc_st->clock_ratio = div64_u64(aclk << 32, pxlclk);
}