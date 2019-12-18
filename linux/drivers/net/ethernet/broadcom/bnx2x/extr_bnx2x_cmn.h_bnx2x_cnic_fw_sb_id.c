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
struct bnx2x {int /*<<< orphan*/  base_fw_ndsb; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 bnx2x_cnic_fw_sb_id(struct bnx2x *bp)
{
	/* the 'first' id is allocated for the cnic */
	return bp->base_fw_ndsb;
}