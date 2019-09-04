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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct ttm_buffer_object {int dummy; } ;
struct ttm_agp_backend {struct ttm_tt ttm; struct agp_bridge_data* bridge; int /*<<< orphan*/ * mem; } ;
struct agp_bridge_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct ttm_agp_backend*) ; 
 struct ttm_agp_backend* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_agp_func ; 
 scalar_t__ ttm_tt_init (struct ttm_tt*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 

struct ttm_tt *ttm_agp_tt_create(struct ttm_buffer_object *bo,
				 struct agp_bridge_data *bridge,
				 uint32_t page_flags)
{
	struct ttm_agp_backend *agp_be;

	agp_be = kmalloc(sizeof(*agp_be), GFP_KERNEL);
	if (!agp_be)
		return NULL;

	agp_be->mem = NULL;
	agp_be->bridge = bridge;
	agp_be->ttm.func = &ttm_agp_func;

	if (ttm_tt_init(&agp_be->ttm, bo, page_flags)) {
		kfree(agp_be);
		return NULL;
	}

	return &agp_be->ttm;
}