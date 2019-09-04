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
struct ttm_placement {int dummy; } ;
struct ttm_buffer_object {int dummy; } ;
struct ast_bo {struct ttm_placement placement; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTM_PL_FLAG_SYSTEM ; 
 struct ast_bo* ast_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ast_ttm_bo_is_ast_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  ast_ttm_placement (struct ast_bo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ast_bo_evict_flags(struct ttm_buffer_object *bo, struct ttm_placement *pl)
{
	struct ast_bo *astbo = ast_bo(bo);

	if (!ast_ttm_bo_is_ast_bo(bo))
		return;

	ast_ttm_placement(astbo, TTM_PL_FLAG_SYSTEM);
	*pl = astbo->placement;
}