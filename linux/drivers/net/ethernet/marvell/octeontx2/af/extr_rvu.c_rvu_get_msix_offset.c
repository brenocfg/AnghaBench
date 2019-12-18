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
typedef  size_t u16 ;
struct TYPE_2__ {size_t max; } ;
struct rvu_pfvf {scalar_t__* msix_lfmap; TYPE_1__ msix; } ;
struct rvu {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSIX_BLKLF (int,int) ; 
 size_t MSIX_VECTOR_INVALID ; 

__attribute__((used)) static u16 rvu_get_msix_offset(struct rvu *rvu, struct rvu_pfvf *pfvf,
			       int blkaddr, int lf)
{
	u16 vec;

	if (lf < 0)
		return MSIX_VECTOR_INVALID;

	for (vec = 0; vec < pfvf->msix.max; vec++) {
		if (pfvf->msix_lfmap[vec] == MSIX_BLKLF(blkaddr, lf))
			return vec;
	}
	return MSIX_VECTOR_INVALID;
}