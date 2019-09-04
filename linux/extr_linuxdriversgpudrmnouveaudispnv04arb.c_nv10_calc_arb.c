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
struct nv_sim_state {int pclk_khz; int nvclk_khz; int mclk_khz; int memory_width; int bpp; scalar_t__ memory_type; int mem_page_miss; scalar_t__ two_heads; } ;
struct nv_fifo_info {int burst; int lwm; } ;

/* Variables and functions */
 void* min (int,int) ; 
 int rounddown_pow_of_two (int) ; 

__attribute__((used)) static void
nv10_calc_arb(struct nv_fifo_info *fifo, struct nv_sim_state *arb)
{
	int fill_rate, drain_rate;
	int pclks, nvclks, mclks, xclks;
	int pclk_freq, nvclk_freq, mclk_freq;
	int fill_lat, extra_lat;
	int max_burst_o, max_burst_l;
	int fifo_len, min_lwm, max_lwm;
	const int burst_lat = 80; /* Maximum allowable latency due
				   * to the CRTC FIFO burst. (ns) */

	pclk_freq = arb->pclk_khz;
	nvclk_freq = arb->nvclk_khz;
	mclk_freq = arb->mclk_khz;

	fill_rate = mclk_freq * arb->memory_width / 8; /* kB/s */
	drain_rate = pclk_freq * arb->bpp / 8; /* kB/s */

	fifo_len = arb->two_heads ? 1536 : 1024; /* B */

	/* Fixed FIFO refill latency. */

	pclks = 4;	/* lwm detect. */

	nvclks = 3	/* lwm -> sync. */
		+ 2	/* fbi bus cycles (1 req + 1 busy) */
		+ 1	/* 2 edge sync.  may be very close to edge so
			 * just put one. */
		+ 1	/* fbi_d_rdv_n */
		+ 1	/* Fbi_d_rdata */
		+ 1;	/* crtfifo load */

	mclks = 1	/* 2 edge sync.  may be very close to edge so
			 * just put one. */
		+ 1	/* arb_hp_req */
		+ 5	/* tiling pipeline */
		+ 2	/* latency fifo */
		+ 2	/* memory request to fbio block */
		+ 7;	/* data returned from fbio block */

	/* Need to accumulate 256 bits for read */
	mclks += (arb->memory_type == 0 ? 2 : 1)
		* arb->memory_width / 32;

	fill_lat = mclks * 1000 * 1000 / mclk_freq   /* minimum mclk latency */
		+ nvclks * 1000 * 1000 / nvclk_freq  /* nvclk latency */
		+ pclks * 1000 * 1000 / pclk_freq;   /* pclk latency */

	/* Conditional FIFO refill latency. */

	xclks = 2 * arb->mem_page_miss + mclks /* Extra latency due to
						* the overlay. */
		+ 2 * arb->mem_page_miss       /* Extra pagemiss latency. */
		+ (arb->bpp == 32 ? 8 : 4);    /* Margin of error. */

	extra_lat = xclks * 1000 * 1000 / mclk_freq;

	if (arb->two_heads)
		/* Account for another CRTC. */
		extra_lat += fill_lat + extra_lat + burst_lat;

	/* FIFO burst */

	/* Max burst not leading to overflows. */
	max_burst_o = (1 + fifo_len - extra_lat * drain_rate / (1000 * 1000))
		* (fill_rate / 1000) / ((fill_rate - drain_rate) / 1000);
	fifo->burst = min(max_burst_o, 1024);

	/* Max burst value with an acceptable latency. */
	max_burst_l = burst_lat * fill_rate / (1000 * 1000);
	fifo->burst = min(max_burst_l, fifo->burst);

	fifo->burst = rounddown_pow_of_two(fifo->burst);

	/* FIFO low watermark */

	min_lwm = (fill_lat + extra_lat) * drain_rate / (1000 * 1000) + 1;
	max_lwm = fifo_len - fifo->burst
		+ fill_lat * drain_rate / (1000 * 1000)
		+ fifo->burst * drain_rate / fill_rate;

	fifo->lwm = min_lwm + 10 * (max_lwm - min_lwm) / 100; /* Empirical. */
}