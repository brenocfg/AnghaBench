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
struct drm_gem_object {int dummy; } ;
struct ast_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ast_bo_unref (struct ast_bo**) ; 
 struct ast_bo* gem_to_ast_bo (struct drm_gem_object*) ; 

void ast_gem_free_object(struct drm_gem_object *obj)
{
	struct ast_bo *ast_bo = gem_to_ast_bo(obj);

	ast_bo_unref(&ast_bo);
}