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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FCOE_IDX (struct bnx2x*) ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 scalar_t__ bnx2x_alloc_fp_mem_at (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnx2x_alloc_fp_mem_cnic(struct bnx2x *bp)
{
	if (!NO_FCOE(bp))
		/* FCoE */
		if (bnx2x_alloc_fp_mem_at(bp, FCOE_IDX(bp)))
			/* we will fail load process instead of mark
			 * NO_FCOE_FLAG
			 */
			return -ENOMEM;

	return 0;
}