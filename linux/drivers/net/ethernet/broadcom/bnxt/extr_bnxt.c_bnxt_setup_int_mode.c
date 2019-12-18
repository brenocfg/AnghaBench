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
struct bnxt {int flags; } ;

/* Variables and functions */
 int BNXT_FLAG_USING_MSIX ; 
 int bnxt_set_real_num_queues (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_setup_inta (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_setup_msix (struct bnxt*) ; 

__attribute__((used)) static int bnxt_setup_int_mode(struct bnxt *bp)
{
	int rc;

	if (bp->flags & BNXT_FLAG_USING_MSIX)
		bnxt_setup_msix(bp);
	else
		bnxt_setup_inta(bp);

	rc = bnxt_set_real_num_queues(bp);
	return rc;
}