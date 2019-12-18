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
typedef  size_t u32 ;
struct imgu_css_pool {int last; TYPE_1__* entry; } ;
struct TYPE_2__ {int valid; } ;

/* Variables and functions */
 int IPU3_CSS_POOL_SIZE ; 

void imgu_css_pool_get(struct imgu_css_pool *pool)
{
	/* Get the oldest entry */
	u32 n = (pool->last + 1) % IPU3_CSS_POOL_SIZE;

	pool->entry[n].valid = true;
	pool->last = n;
}