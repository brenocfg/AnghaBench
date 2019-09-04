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
 int /*<<< orphan*/  DISPATCH_LOG_BYTES ; 
 int alloc_dispatch_logs () ; 
 int /*<<< orphan*/  dtl_cache ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int alloc_dispatch_log_kmem_cache(void)
{
	dtl_cache = kmem_cache_create("dtl", DISPATCH_LOG_BYTES,
						DISPATCH_LOG_BYTES, 0, NULL);
	if (!dtl_cache) {
		pr_warn("Failed to create dispatch trace log buffer cache\n");
		pr_warn("Stolen time statistics will be unreliable\n");
		return 0;
	}

	return alloc_dispatch_logs();
}