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
struct drm_device {struct ast_private* dev_private; } ;
struct ast_private {int /*<<< orphan*/  cursor_cache; int /*<<< orphan*/  cache_kmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ast_cursor_fini(struct drm_device *dev)
{
	struct ast_private *ast = dev->dev_private;
	ttm_bo_kunmap(&ast->cache_kmap);
	drm_gem_object_put_unlocked(ast->cursor_cache);
}