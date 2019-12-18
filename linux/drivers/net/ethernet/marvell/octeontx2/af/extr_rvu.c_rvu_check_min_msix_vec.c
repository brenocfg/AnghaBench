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
struct rvu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RVU_AF_INT_VEC_CNT ; 
 int RVU_PF_INT_VEC_CNT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static void rvu_check_min_msix_vec(struct rvu *rvu, int nvecs, int pf, int vf)
{
	int min_vecs;

	if (!vf)
		goto check_pf;

	if (!nvecs) {
		dev_warn(rvu->dev,
			 "PF%d:VF%d is configured with zero msix vectors, %d\n",
			 pf, vf - 1, nvecs);
	}
	return;

check_pf:
	if (pf == 0)
		min_vecs = RVU_AF_INT_VEC_CNT + RVU_PF_INT_VEC_CNT;
	else
		min_vecs = RVU_PF_INT_VEC_CNT;

	if (!(nvecs < min_vecs))
		return;
	dev_warn(rvu->dev,
		 "PF%d is configured with too few vectors, %d, min is %d\n",
		 pf, nvecs, min_vecs);
}