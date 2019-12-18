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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ide_timing {scalar_t__ udma; } ;

/* Variables and functions */
 int TR_100_UDMAREG_UDMA_EN ; 
 int TR_100_UDMAREG_UDMA_MASK ; 
 scalar_t__ XFER_UDMA_5 ; 
 struct ide_timing* ide_timing_find_mode (scalar_t__) ; 
 int kauai_lookup_timing (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kauai_udma_timings ; 

__attribute__((used)) static int
set_timings_udma_ata6(u32 *pio_timings, u32 *ultra_timings, u8 speed)
{
	struct ide_timing *t = ide_timing_find_mode(speed);
	u32 tr;

	if (speed > XFER_UDMA_5 || t == NULL)
		return 1;
	tr = kauai_lookup_timing(kauai_udma_timings, (int)t->udma);
	*ultra_timings = ((*ultra_timings) & ~TR_100_UDMAREG_UDMA_MASK) | tr;
	*ultra_timings = (*ultra_timings) | TR_100_UDMAREG_UDMA_EN;

	return 0;
}