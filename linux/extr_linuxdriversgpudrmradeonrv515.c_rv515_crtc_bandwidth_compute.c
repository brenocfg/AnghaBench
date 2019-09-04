#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_20__ {scalar_t__ full; } ;
struct TYPE_15__ {scalar_t__ full; } ;
struct TYPE_14__ {scalar_t__ full; } ;
struct TYPE_18__ {void* full; } ;
struct rv515_watermark {int lb_request_fifo_depth; TYPE_7__ priority_mark; TYPE_7__ priority_mark_max; TYPE_2__ worst_case_latency; TYPE_1__ dbpp; TYPE_7__ num_line_pair; TYPE_7__ active_time; TYPE_5__ consumption_rate; } ;
struct TYPE_16__ {scalar_t__ pm_method; int current_sclk; scalar_t__ dpm_enabled; } ;
struct radeon_device {scalar_t__ family; TYPE_3__ pm; } ;
struct drm_display_mode {int crtc_hdisplay; int clock; int crtc_htotal; } ;
struct TYPE_19__ {struct drm_display_mode mode; int /*<<< orphan*/  enabled; } ;
struct TYPE_17__ {scalar_t__ full; } ;
struct radeon_crtc {scalar_t__ rmx_type; TYPE_6__ base; TYPE_7__ hsc; TYPE_4__ vsc; } ;
typedef  TYPE_7__ fixed20_12 ;

/* Variables and functions */
 scalar_t__ CHIP_RV610 ; 
 scalar_t__ PM_METHOD_DPM ; 
 scalar_t__ RMX_OFF ; 
 void* dfixed_ceil (TYPE_7__) ; 
 scalar_t__ dfixed_const (int) ; 
 void* dfixed_div (TYPE_7__,TYPE_7__) ; 
 void* dfixed_mul (TYPE_7__,TYPE_7__) ; 
 int dfixed_trunc (TYPE_7__) ; 
 int radeon_dpm_get_sclk (struct radeon_device*,int) ; 

__attribute__((used)) static void rv515_crtc_bandwidth_compute(struct radeon_device *rdev,
					 struct radeon_crtc *crtc,
					 struct rv515_watermark *wm,
					 bool low)
{
	struct drm_display_mode *mode = &crtc->base.mode;
	fixed20_12 a, b, c;
	fixed20_12 pclk, request_fifo_depth, tolerable_latency, estimated_width;
	fixed20_12 consumption_time, line_time, chunk_time, read_delay_latency;
	fixed20_12 sclk;
	u32 selected_sclk;

	if (!crtc->base.enabled) {
		/* FIXME: wouldn't it better to set priority mark to maximum */
		wm->lb_request_fifo_depth = 4;
		return;
	}

	/* rv6xx, rv7xx */
	if ((rdev->family >= CHIP_RV610) &&
	    (rdev->pm.pm_method == PM_METHOD_DPM) && rdev->pm.dpm_enabled)
		selected_sclk = radeon_dpm_get_sclk(rdev, low);
	else
		selected_sclk = rdev->pm.current_sclk;

	/* sclk in Mhz */
	a.full = dfixed_const(100);
	sclk.full = dfixed_const(selected_sclk);
	sclk.full = dfixed_div(sclk, a);

	if (crtc->vsc.full > dfixed_const(2))
		wm->num_line_pair.full = dfixed_const(2);
	else
		wm->num_line_pair.full = dfixed_const(1);

	b.full = dfixed_const(mode->crtc_hdisplay);
	c.full = dfixed_const(256);
	a.full = dfixed_div(b, c);
	request_fifo_depth.full = dfixed_mul(a, wm->num_line_pair);
	request_fifo_depth.full = dfixed_ceil(request_fifo_depth);
	if (a.full < dfixed_const(4)) {
		wm->lb_request_fifo_depth = 4;
	} else {
		wm->lb_request_fifo_depth = dfixed_trunc(request_fifo_depth);
	}

	/* Determine consumption rate
	 *  pclk = pixel clock period(ns) = 1000 / (mode.clock / 1000)
	 *  vtaps = number of vertical taps,
	 *  vsc = vertical scaling ratio, defined as source/destination
	 *  hsc = horizontal scaling ration, defined as source/destination
	 */
	a.full = dfixed_const(mode->clock);
	b.full = dfixed_const(1000);
	a.full = dfixed_div(a, b);
	pclk.full = dfixed_div(b, a);
	if (crtc->rmx_type != RMX_OFF) {
		b.full = dfixed_const(2);
		if (crtc->vsc.full > b.full)
			b.full = crtc->vsc.full;
		b.full = dfixed_mul(b, crtc->hsc);
		c.full = dfixed_const(2);
		b.full = dfixed_div(b, c);
		consumption_time.full = dfixed_div(pclk, b);
	} else {
		consumption_time.full = pclk.full;
	}
	a.full = dfixed_const(1);
	wm->consumption_rate.full = dfixed_div(a, consumption_time);


	/* Determine line time
	 *  LineTime = total time for one line of displayhtotal
	 *  LineTime = total number of horizontal pixels
	 *  pclk = pixel clock period(ns)
	 */
	a.full = dfixed_const(crtc->base.mode.crtc_htotal);
	line_time.full = dfixed_mul(a, pclk);

	/* Determine active time
	 *  ActiveTime = time of active region of display within one line,
	 *  hactive = total number of horizontal active pixels
	 *  htotal = total number of horizontal pixels
	 */
	a.full = dfixed_const(crtc->base.mode.crtc_htotal);
	b.full = dfixed_const(crtc->base.mode.crtc_hdisplay);
	wm->active_time.full = dfixed_mul(line_time, b);
	wm->active_time.full = dfixed_div(wm->active_time, a);

	/* Determine chunk time
	 * ChunkTime = the time it takes the DCP to send one chunk of data
	 * to the LB which consists of pipeline delay and inter chunk gap
	 * sclk = system clock(Mhz)
	 */
	a.full = dfixed_const(600 * 1000);
	chunk_time.full = dfixed_div(a, sclk);
	read_delay_latency.full = dfixed_const(1000);

	/* Determine the worst case latency
	 * NumLinePair = Number of line pairs to request(1=2 lines, 2=4 lines)
	 * WorstCaseLatency = worst case time from urgent to when the MC starts
	 *                    to return data
	 * READ_DELAY_IDLE_MAX = constant of 1us
	 * ChunkTime = time it takes the DCP to send one chunk of data to the LB
	 *             which consists of pipeline delay and inter chunk gap
	 */
	if (dfixed_trunc(wm->num_line_pair) > 1) {
		a.full = dfixed_const(3);
		wm->worst_case_latency.full = dfixed_mul(a, chunk_time);
		wm->worst_case_latency.full += read_delay_latency.full;
	} else {
		wm->worst_case_latency.full = chunk_time.full + read_delay_latency.full;
	}

	/* Determine the tolerable latency
	 * TolerableLatency = Any given request has only 1 line time
	 *                    for the data to be returned
	 * LBRequestFifoDepth = Number of chunk requests the LB can
	 *                      put into the request FIFO for a display
	 *  LineTime = total time for one line of display
	 *  ChunkTime = the time it takes the DCP to send one chunk
	 *              of data to the LB which consists of
	 *  pipeline delay and inter chunk gap
	 */
	if ((2+wm->lb_request_fifo_depth) >= dfixed_trunc(request_fifo_depth)) {
		tolerable_latency.full = line_time.full;
	} else {
		tolerable_latency.full = dfixed_const(wm->lb_request_fifo_depth - 2);
		tolerable_latency.full = request_fifo_depth.full - tolerable_latency.full;
		tolerable_latency.full = dfixed_mul(tolerable_latency, chunk_time);
		tolerable_latency.full = line_time.full - tolerable_latency.full;
	}
	/* We assume worst case 32bits (4 bytes) */
	wm->dbpp.full = dfixed_const(2 * 16);

	/* Determine the maximum priority mark
	 *  width = viewport width in pixels
	 */
	a.full = dfixed_const(16);
	wm->priority_mark_max.full = dfixed_const(crtc->base.mode.crtc_hdisplay);
	wm->priority_mark_max.full = dfixed_div(wm->priority_mark_max, a);
	wm->priority_mark_max.full = dfixed_ceil(wm->priority_mark_max);

	/* Determine estimated width */
	estimated_width.full = tolerable_latency.full - wm->worst_case_latency.full;
	estimated_width.full = dfixed_div(estimated_width, consumption_time);
	if (dfixed_trunc(estimated_width) > crtc->base.mode.crtc_hdisplay) {
		wm->priority_mark.full = wm->priority_mark_max.full;
	} else {
		a.full = dfixed_const(16);
		wm->priority_mark.full = dfixed_div(estimated_width, a);
		wm->priority_mark.full = dfixed_ceil(wm->priority_mark);
		wm->priority_mark.full = wm->priority_mark_max.full - wm->priority_mark.full;
	}
}