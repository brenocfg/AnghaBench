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
struct dcn20_resource_pool {int dummy; } ;

/* Variables and functions */
 struct dcn20_resource_pool* TO_DCN20_RES_POOL (struct resource_pool*) ; 
 int /*<<< orphan*/  destruct (struct dcn20_resource_pool*) ; 
 int /*<<< orphan*/  kfree (struct dcn20_resource_pool*) ; 

__attribute__((used)) static void dcn20_destroy_resource_pool(struct resource_pool **pool)
{
	struct dcn20_resource_pool *dcn20_pool = TO_DCN20_RES_POOL(*pool);

	destruct(dcn20_pool);
	kfree(dcn20_pool);
	*pool = NULL;
}