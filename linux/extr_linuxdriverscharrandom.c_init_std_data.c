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
struct entropy_store {TYPE_1__* poolinfo; int /*<<< orphan*/  last_pulled; } ;
typedef  int /*<<< orphan*/  rv ;
typedef  int /*<<< orphan*/  now ;
typedef  unsigned long ktime_t ;
struct TYPE_2__ {int poolbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_get_random_long (unsigned long*) ; 
 int /*<<< orphan*/  arch_get_random_seed_long (unsigned long*) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long ktime_get_real () ; 
 int /*<<< orphan*/  mix_pool_bytes (struct entropy_store*,unsigned long*,int) ; 
 unsigned long random_get_entropy () ; 
 unsigned long* utsname () ; 

__attribute__((used)) static void init_std_data(struct entropy_store *r)
{
	int i;
	ktime_t now = ktime_get_real();
	unsigned long rv;

	r->last_pulled = jiffies;
	mix_pool_bytes(r, &now, sizeof(now));
	for (i = r->poolinfo->poolbytes; i > 0; i -= sizeof(rv)) {
		if (!arch_get_random_seed_long(&rv) &&
		    !arch_get_random_long(&rv))
			rv = random_get_entropy();
		mix_pool_bytes(r, &rv, sizeof(rv));
	}
	mix_pool_bytes(r, utsname(), sizeof(*(utsname())));
}