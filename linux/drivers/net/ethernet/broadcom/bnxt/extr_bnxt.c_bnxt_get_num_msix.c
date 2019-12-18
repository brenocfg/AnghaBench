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
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_NEW_RM (struct bnxt*) ; 
 int bnxt_get_max_func_irqs (struct bnxt*) ; 
 int bnxt_nq_rings_in_use (struct bnxt*) ; 

__attribute__((used)) static int bnxt_get_num_msix(struct bnxt *bp)
{
	if (!BNXT_NEW_RM(bp))
		return bnxt_get_max_func_irqs(bp);

	return bnxt_nq_rings_in_use(bp);
}