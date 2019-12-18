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
struct ion_page_pool {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ion_page_pool*) ; 

void ion_page_pool_destroy(struct ion_page_pool *pool)
{
	kfree(pool);
}