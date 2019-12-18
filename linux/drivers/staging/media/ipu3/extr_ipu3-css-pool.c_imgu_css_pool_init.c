#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imgu_device {int dummy; } ;
struct imgu_css_pool {unsigned int last; TYPE_1__* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vaddr; } ;
struct TYPE_3__ {int valid; TYPE_2__ param; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int IPU3_CSS_POOL_SIZE ; 
 int /*<<< orphan*/  imgu_css_pool_cleanup (struct imgu_device*,struct imgu_css_pool*) ; 
 int /*<<< orphan*/  imgu_dmamap_alloc (struct imgu_device*,TYPE_2__*,size_t) ; 

int imgu_css_pool_init(struct imgu_device *imgu, struct imgu_css_pool *pool,
		       size_t size)
{
	unsigned int i;

	for (i = 0; i < IPU3_CSS_POOL_SIZE; i++) {
		pool->entry[i].valid = false;
		if (size == 0) {
			pool->entry[i].param.vaddr = NULL;
			continue;
		}

		if (!imgu_dmamap_alloc(imgu, &pool->entry[i].param, size))
			goto fail;
	}

	pool->last = IPU3_CSS_POOL_SIZE;

	return 0;

fail:
	imgu_css_pool_cleanup(imgu, pool);
	return -ENOMEM;
}