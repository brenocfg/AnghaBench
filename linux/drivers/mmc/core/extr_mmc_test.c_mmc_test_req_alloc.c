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
struct mmc_test_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mmc_test_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_test_req_reset (struct mmc_test_req*) ; 

__attribute__((used)) static struct mmc_test_req *mmc_test_req_alloc(void)
{
	struct mmc_test_req *rq = kmalloc(sizeof(*rq), GFP_KERNEL);

	if (rq)
		mmc_test_req_reset(rq);

	return rq;
}