#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_device {struct ast_private* dev_private; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; } ;
struct ast_private {TYPE_1__ ttm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bdev; } ;
struct ast_bo {int /*<<< orphan*/  placement; TYPE_2__ bo; int /*<<< orphan*/  gem; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int TTM_PL_FLAG_SYSTEM ; 
 int TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  ast_bo_ttm_destroy ; 
 int /*<<< orphan*/  ast_ttm_placement (struct ast_bo*,int) ; 
 int drm_gem_object_init (struct drm_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct ast_bo*) ; 
 struct ast_bo* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t ttm_bo_dma_acc_size (int /*<<< orphan*/ *,int,int) ; 
 int ttm_bo_init (int /*<<< orphan*/ *,TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_type_device ; 

int ast_bo_create(struct drm_device *dev, int size, int align,
		  uint32_t flags, struct ast_bo **pastbo)
{
	struct ast_private *ast = dev->dev_private;
	struct ast_bo *astbo;
	size_t acc_size;
	int ret;

	astbo = kzalloc(sizeof(struct ast_bo), GFP_KERNEL);
	if (!astbo)
		return -ENOMEM;

	ret = drm_gem_object_init(dev, &astbo->gem, size);
	if (ret)
		goto error;

	astbo->bo.bdev = &ast->ttm.bdev;

	ast_ttm_placement(astbo, TTM_PL_FLAG_VRAM | TTM_PL_FLAG_SYSTEM);

	acc_size = ttm_bo_dma_acc_size(&ast->ttm.bdev, size,
				       sizeof(struct ast_bo));

	ret = ttm_bo_init(&ast->ttm.bdev, &astbo->bo, size,
			  ttm_bo_type_device, &astbo->placement,
			  align >> PAGE_SHIFT, false, acc_size,
			  NULL, NULL, ast_bo_ttm_destroy);
	if (ret)
		goto error;

	*pastbo = astbo;
	return 0;
error:
	kfree(astbo);
	return ret;
}