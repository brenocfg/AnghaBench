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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct MR_QUAD_ELEMENT* quad; int /*<<< orphan*/  noElements; } ;
struct MR_SPAN_BLOCK_INFO {TYPE_1__ block_span_info; } ;
struct MR_QUAD_ELEMENT {int /*<<< orphan*/  offsetInSpan; int /*<<< orphan*/  diff; int /*<<< orphan*/  logStart; int /*<<< orphan*/  logEnd; } ;
struct MR_LD_RAID {scalar_t__ spanDepth; int stripeShift; } ;
struct MR_DRV_RAID_MAP_ALL {int dummy; } ;

/* Variables and functions */
 struct MR_LD_RAID* MR_LdRaidGet (scalar_t__,struct MR_DRV_RAID_MAP_ALL*) ; 
 struct MR_SPAN_BLOCK_INFO* MR_LdSpanInfoGet (scalar_t__,struct MR_DRV_RAID_MAP_ALL*) ; 
 scalar_t__ SPAN_INVALID ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int mega_div64_32 (int,scalar_t__) ; 
 scalar_t__ mega_mod64 (int,scalar_t__) ; 

u32 MR_GetSpanBlock(u32 ld, u64 row, u64 *span_blk,
		    struct MR_DRV_RAID_MAP_ALL *map)
{
	struct MR_SPAN_BLOCK_INFO *pSpanBlock = MR_LdSpanInfoGet(ld, map);
	struct MR_QUAD_ELEMENT    *quad;
	struct MR_LD_RAID         *raid = MR_LdRaidGet(ld, map);
	u32                span, j;

	for (span = 0; span < raid->spanDepth; span++, pSpanBlock++) {

		for (j = 0; j < le32_to_cpu(pSpanBlock->block_span_info.noElements); j++) {
			quad = &pSpanBlock->block_span_info.quad[j];

			if (le32_to_cpu(quad->diff) == 0)
				return SPAN_INVALID;
			if (le64_to_cpu(quad->logStart) <= row && row <=
				le64_to_cpu(quad->logEnd) && (mega_mod64(row - le64_to_cpu(quad->logStart),
				le32_to_cpu(quad->diff))) == 0) {
				if (span_blk != NULL) {
					u64  blk, debugBlk;
					blk =  mega_div64_32((row-le64_to_cpu(quad->logStart)), le32_to_cpu(quad->diff));
					debugBlk = blk;

					blk = (blk + le64_to_cpu(quad->offsetInSpan)) << raid->stripeShift;
					*span_blk = blk;
				}
				return span;
			}
		}
	}
	return SPAN_INVALID;
}