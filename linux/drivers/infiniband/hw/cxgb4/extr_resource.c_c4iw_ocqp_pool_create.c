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
struct c4iw_rdev {int /*<<< orphan*/  ocqp_pool; TYPE_3__ lldi; } ;
struct TYPE_4__ {unsigned int start; unsigned int size; } ;
struct TYPE_5__ {TYPE_1__ ocq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MIN_OCQP_SHIFT ; 
 scalar_t__ gen_pool_add (int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  gen_pool_create (int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int,unsigned int) ; 

int c4iw_ocqp_pool_create(struct c4iw_rdev *rdev)
{
	unsigned start, chunk, top;

	rdev->ocqp_pool = gen_pool_create(MIN_OCQP_SHIFT, -1);
	if (!rdev->ocqp_pool)
		return -ENOMEM;

	start = rdev->lldi.vr->ocq.start;
	chunk = rdev->lldi.vr->ocq.size;
	top = start + chunk;

	while (start < top) {
		chunk = min(top - start + 1, chunk);
		if (gen_pool_add(rdev->ocqp_pool, start, chunk, -1)) {
			pr_debug("failed to add OCQP chunk (%x/%x)\n",
				 start, chunk);
			if (chunk <= 1024 << MIN_OCQP_SHIFT) {
				pr_warn("Failed to add all OCQP chunks (%x/%x)\n",
					start, top - start);
				return 0;
			}
			chunk >>= 1;
		} else {
			pr_debug("added OCQP chunk (%x/%x)\n",
				 start, chunk);
			start += chunk;
		}
	}
	return 0;
}