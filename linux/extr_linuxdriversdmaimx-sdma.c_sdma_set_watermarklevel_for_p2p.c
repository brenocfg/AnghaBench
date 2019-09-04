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
struct sdma_engine {scalar_t__ spba_start_addr; scalar_t__ spba_end_addr; } ;
struct sdma_channel {int watermark_level; int event_id0; int event_id1; scalar_t__ per_address2; scalar_t__ per_address; int /*<<< orphan*/ * event_mask; struct sdma_engine* sdma; } ;

/* Variables and functions */
 int SDMA_WATERMARK_LEVEL_CONT ; 
 int SDMA_WATERMARK_LEVEL_DP ; 
 int SDMA_WATERMARK_LEVEL_HWE ; 
 int SDMA_WATERMARK_LEVEL_HWML ; 
 int SDMA_WATERMARK_LEVEL_LWE ; 
 int SDMA_WATERMARK_LEVEL_LWML ; 
 int SDMA_WATERMARK_LEVEL_SP ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdma_set_watermarklevel_for_p2p(struct sdma_channel *sdmac)
{
	struct sdma_engine *sdma = sdmac->sdma;

	int lwml = sdmac->watermark_level & SDMA_WATERMARK_LEVEL_LWML;
	int hwml = (sdmac->watermark_level & SDMA_WATERMARK_LEVEL_HWML) >> 16;

	set_bit(sdmac->event_id0 % 32, &sdmac->event_mask[1]);
	set_bit(sdmac->event_id1 % 32, &sdmac->event_mask[0]);

	if (sdmac->event_id0 > 31)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_LWE;

	if (sdmac->event_id1 > 31)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_HWE;

	/*
	 * If LWML(src_maxburst) > HWML(dst_maxburst), we need
	 * swap LWML and HWML of INFO(A.3.2.5.1), also need swap
	 * r0(event_mask[1]) and r1(event_mask[0]).
	 */
	if (lwml > hwml) {
		sdmac->watermark_level &= ~(SDMA_WATERMARK_LEVEL_LWML |
						SDMA_WATERMARK_LEVEL_HWML);
		sdmac->watermark_level |= hwml;
		sdmac->watermark_level |= lwml << 16;
		swap(sdmac->event_mask[0], sdmac->event_mask[1]);
	}

	if (sdmac->per_address2 >= sdma->spba_start_addr &&
			sdmac->per_address2 <= sdma->spba_end_addr)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_SP;

	if (sdmac->per_address >= sdma->spba_start_addr &&
			sdmac->per_address <= sdma->spba_end_addr)
		sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_DP;

	sdmac->watermark_level |= SDMA_WATERMARK_LEVEL_CONT;
}