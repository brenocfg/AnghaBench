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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ full; } ;
struct dce8_wm_params {scalar_t__ lb_size; scalar_t__ src_width; scalar_t__ active_time; scalar_t__ blank_time; scalar_t__ vtaps; TYPE_1__ vsc; } ;
struct TYPE_4__ {scalar_t__ full; } ;
typedef  TYPE_2__ fixed20_12 ;

/* Variables and functions */
 scalar_t__ dce_v8_0_latency_watermark (struct dce8_wm_params*) ; 
 scalar_t__ dfixed_const (int) ; 

__attribute__((used)) static bool dce_v8_0_check_latency_hiding(struct dce8_wm_params *wm)
{
	u32 lb_partitions = wm->lb_size / wm->src_width;
	u32 line_time = wm->active_time + wm->blank_time;
	u32 latency_tolerant_lines;
	u32 latency_hiding;
	fixed20_12 a;

	a.full = dfixed_const(1);
	if (wm->vsc.full > a.full)
		latency_tolerant_lines = 1;
	else {
		if (lb_partitions <= (wm->vtaps + 1))
			latency_tolerant_lines = 1;
		else
			latency_tolerant_lines = 2;
	}

	latency_hiding = (latency_tolerant_lines * line_time + wm->blank_time);

	if (dce_v8_0_latency_watermark(wm) <= latency_hiding)
		return true;
	else
		return false;
}