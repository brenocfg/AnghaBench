#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {void* full; } ;
struct evergreen_wm_params {int active_time; int blank_time; int bytes_per_pixel; int src_width; TYPE_1__ vsc; } ;
typedef  TYPE_1__ fixed20_12 ;

/* Variables and functions */
 void* dfixed_const (int) ; 
 void* dfixed_div (TYPE_1__,TYPE_1__) ; 
 void* dfixed_mul (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  dfixed_trunc (TYPE_1__) ; 

__attribute__((used)) static u32 evergreen_average_bandwidth(struct evergreen_wm_params *wm)
{
	/* Calculate the display mode Average Bandwidth
	 * DisplayMode should contain the source and destination dimensions,
	 * timing, etc.
	 */
	fixed20_12 bpp;
	fixed20_12 line_time;
	fixed20_12 src_width;
	fixed20_12 bandwidth;
	fixed20_12 a;

	a.full = dfixed_const(1000);
	line_time.full = dfixed_const(wm->active_time + wm->blank_time);
	line_time.full = dfixed_div(line_time, a);
	bpp.full = dfixed_const(wm->bytes_per_pixel);
	src_width.full = dfixed_const(wm->src_width);
	bandwidth.full = dfixed_mul(src_width, bpp);
	bandwidth.full = dfixed_mul(bandwidth, wm->vsc);
	bandwidth.full = dfixed_div(bandwidth, line_time);

	return dfixed_trunc(bandwidth);
}