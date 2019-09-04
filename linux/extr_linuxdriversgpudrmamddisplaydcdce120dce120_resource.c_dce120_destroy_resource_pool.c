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
struct dce110_resource_pool {int dummy; } ;

/* Variables and functions */
 struct dce110_resource_pool* TO_DCE110_RES_POOL (struct resource_pool*) ; 
 int /*<<< orphan*/  destruct (struct dce110_resource_pool*) ; 
 int /*<<< orphan*/  kfree (struct dce110_resource_pool*) ; 

__attribute__((used)) static void dce120_destroy_resource_pool(struct resource_pool **pool)
{
	struct dce110_resource_pool *dce110_pool = TO_DCE110_RES_POOL(*pool);

	destruct(dce110_pool);
	kfree(dce110_pool);
	*pool = NULL;
}