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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct b44 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B44_FILT_ADDR ; 
 int /*<<< orphan*/  B44_FILT_DATA ; 
 int /*<<< orphan*/  bw32 (struct b44*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bwfilter_table(struct b44 *bp, u8 *pp, u32 bytes, u32 table_offset)
{
	u32 i;
	u32 *pattern = (u32 *) pp;

	for (i = 0; i < bytes; i += sizeof(u32)) {
		bw32(bp, B44_FILT_ADDR, table_offset + i);
		bw32(bp, B44_FILT_DATA, pattern[i / sizeof(u32)]);
	}
}