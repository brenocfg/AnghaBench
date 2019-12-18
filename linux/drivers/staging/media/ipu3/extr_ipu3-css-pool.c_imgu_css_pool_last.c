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
struct imgu_css_pool {unsigned int last; TYPE_1__* entry; } ;
struct imgu_css_map {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {struct imgu_css_map const param; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 unsigned int IPU3_CSS_POOL_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

const struct imgu_css_map *
imgu_css_pool_last(struct imgu_css_pool *pool, unsigned int n)
{
	static const struct imgu_css_map null_map = { 0 };
	int i = (pool->last + IPU3_CSS_POOL_SIZE - n) % IPU3_CSS_POOL_SIZE;

	WARN_ON(n >= IPU3_CSS_POOL_SIZE);

	if (!pool->entry[i].valid)
		return &null_map;

	return &pool->entry[i].param;
}