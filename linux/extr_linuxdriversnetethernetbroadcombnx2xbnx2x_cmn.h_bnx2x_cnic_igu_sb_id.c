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
struct bnx2x {int /*<<< orphan*/  igu_base_sb; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 bnx2x_cnic_igu_sb_id(struct bnx2x *bp)
{
	return bp->igu_base_sb;
}