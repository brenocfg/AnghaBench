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
struct TYPE_2__ {size_t len; void* content; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (size_t) ; 
 TYPE_1__ hmcdrv_cache_file ; 
 int /*<<< orphan*/  hmcdrv_cache_order ; 
 int /*<<< orphan*/  pr_debug (char*,size_t) ; 
 int /*<<< orphan*/  pr_err (char*,size_t) ; 

int hmcdrv_cache_startup(size_t cachesize)
{
	if (cachesize > 0) { /* perform caching ? */
		hmcdrv_cache_order = get_order(cachesize);
		hmcdrv_cache_file.content =
			(void *) __get_free_pages(GFP_KERNEL | GFP_DMA,
						  hmcdrv_cache_order);

		if (!hmcdrv_cache_file.content) {
			pr_err("Allocating the requested cache size of %zu bytes failed\n",
			       cachesize);
			return -ENOMEM;
		}

		pr_debug("content cache enabled, size is %zu bytes\n",
			 cachesize);
	}

	hmcdrv_cache_file.len = cachesize;
	return 0;
}