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
struct resource_pool {int dummy; } ;
struct dcn10_resource_pool {int dummy; } ;

/* Variables and functions */
 struct dcn10_resource_pool* TO_DCN10_RES_POOL (struct resource_pool*) ; 
 int /*<<< orphan*/  destruct (struct dcn10_resource_pool*) ; 
 int /*<<< orphan*/  kfree (struct dcn10_resource_pool*) ; 

__attribute__((used)) static void dcn10_destroy_resource_pool(struct resource_pool **pool)
{
	struct dcn10_resource_pool *dcn10_pool = TO_DCN10_RES_POOL(*pool);

	destruct(dcn10_pool);
	kfree(dcn10_pool);
	*pool = NULL;
}