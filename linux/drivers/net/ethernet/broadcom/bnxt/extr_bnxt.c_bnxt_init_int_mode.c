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
 int BNXT_FLAG_MSIX_CAP ; 
 int BNXT_FLAG_USING_MSIX ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int bnxt_init_inta (struct bnxt*) ; 
 int bnxt_init_msix (struct bnxt*) ; 

__attribute__((used)) static int bnxt_init_int_mode(struct bnxt *bp)
{
	int rc = 0;

	if (bp->flags & BNXT_FLAG_MSIX_CAP)
		rc = bnxt_init_msix(bp);

	if (!(bp->flags & BNXT_FLAG_USING_MSIX) && BNXT_PF(bp)) {
		/* fallback to INTA */
		rc = bnxt_init_inta(bp);
	}
	return rc;
}