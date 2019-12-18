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
struct imgu_device {int dummy; } ;
struct imgu_css_pool {TYPE_1__* entry; } ;
struct TYPE_2__ {int /*<<< orphan*/  param; } ;

/* Variables and functions */
 unsigned int IPU3_CSS_POOL_SIZE ; 
 int /*<<< orphan*/  imgu_dmamap_free (struct imgu_device*,int /*<<< orphan*/ *) ; 

void imgu_css_pool_cleanup(struct imgu_device *imgu, struct imgu_css_pool *pool)
{
	unsigned int i;

	for (i = 0; i < IPU3_CSS_POOL_SIZE; i++)
		imgu_dmamap_free(imgu, &pool->entry[i].param);
}