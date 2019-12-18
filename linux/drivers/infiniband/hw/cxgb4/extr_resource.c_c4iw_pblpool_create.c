#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* vr; } ;
struct c4iw_rdev {int /*<<< orphan*/  pbl_pool; TYPE_3__ lldi; } ;
struct TYPE_4__ {unsigned int start; unsigned int size; } ;
struct TYPE_5__ {TYPE_1__ pbl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MIN_PBL_SHIFT ; 
 scalar_t__ gen_pool_add (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  gen_pool_create (int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int) ; 

int c4iw_pblpool_create(struct c4iw_rdev *rdev)
{
	unsigned pbl_start, pbl_chunk, pbl_top;

	rdev->pbl_pool = gen_pool_create(MIN_PBL_SHIFT, -1);
	if (!rdev->pbl_pool)
		return -ENOMEM;

	pbl_start = rdev->lldi.vr->pbl.start;
	pbl_chunk = rdev->lldi.vr->pbl.size;
	pbl_top = pbl_start + pbl_chunk;

	while (pbl_start < pbl_top) {
		pbl_chunk = min(pbl_top - pbl_start + 1, pbl_chunk);
		if (gen_pool_add(rdev->pbl_pool, pbl_start, pbl_chunk, -1)) {
			pr_debug("failed to add PBL chunk (%x/%x)\n",
				 pbl_start, pbl_chunk);
			if (pbl_chunk <= 1024 << MIN_PBL_SHIFT) {
				pr_warn("Failed to add all PBL chunks (%x/%x)\n",
					pbl_start, pbl_top - pbl_start);
				return 0;
			}
			pbl_chunk >>= 1;
		} else {
			pr_debug("added PBL chunk (%x/%x)\n",
				 pbl_start, pbl_chunk);
			pbl_start += pbl_chunk;
		}
	}

	return 0;
}