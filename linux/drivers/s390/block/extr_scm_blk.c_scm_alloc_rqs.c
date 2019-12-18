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

/* Variables and functions */
 int ENOMEM ; 
 int __scm_alloc_rq () ; 
 int /*<<< orphan*/  aidaw_pool ; 
 int /*<<< orphan*/  max (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  mempool_create_page_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scm_alloc_rqs(unsigned int nrqs)
{
	int ret = 0;

	aidaw_pool = mempool_create_page_pool(max(nrqs/8, 1U), 0);
	if (!aidaw_pool)
		return -ENOMEM;

	while (nrqs-- && !ret)
		ret = __scm_alloc_rq();

	return ret;
}