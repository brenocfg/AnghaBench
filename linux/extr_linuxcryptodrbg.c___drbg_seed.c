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
struct list_head {int dummy; } ;
struct drbg_state {int seeded; int reseed_ctr; TYPE_1__* d_ops; } ;
struct TYPE_2__ {int (* update ) (struct drbg_state*,struct list_head*,int) ;} ;

/* Variables and functions */
 int stub1 (struct drbg_state*,struct list_head*,int) ; 

__attribute__((used)) static inline int __drbg_seed(struct drbg_state *drbg, struct list_head *seed,
			      int reseed)
{
	int ret = drbg->d_ops->update(drbg, seed, reseed);

	if (ret)
		return ret;

	drbg->seeded = true;
	/* 10.1.1.2 / 10.1.1.3 step 5 */
	drbg->reseed_ctr = 1;

	return ret;
}