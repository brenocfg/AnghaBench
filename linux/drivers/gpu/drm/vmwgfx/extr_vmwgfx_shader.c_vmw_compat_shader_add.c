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
typedef  int /*<<< orphan*/  u32 ;
struct vmw_resource {int dummy; } ;
struct vmw_private {int dummy; } ;
struct vmw_cmdbuf_res_manager {int dummy; } ;
struct vmw_buffer_object {int /*<<< orphan*/  base; } ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct ttm_bo_kmap_obj {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  SVGA3dShaderType ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct vmw_buffer_object* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int ttm_bo_kmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct ttm_bo_kmap_obj*) ; 
 int /*<<< orphan*/  ttm_bo_kunmap (struct ttm_bo_kmap_obj*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_kmap_obj_virtual (struct ttm_bo_kmap_obj*,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_bo_bo_free ; 
 int vmw_bo_init (struct vmw_private*,struct vmw_buffer_object*,size_t,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_bo_unreference (struct vmw_buffer_object**) ; 
 int vmw_cmdbuf_res_add (struct vmw_cmdbuf_res_manager*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmw_resource*,struct list_head*) ; 
 int /*<<< orphan*/  vmw_cmdbuf_res_shader ; 
 int /*<<< orphan*/  vmw_resource_unreference (struct vmw_resource**) ; 
 struct vmw_resource* vmw_shader_alloc (struct vmw_private*,struct vmw_buffer_object*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_shader_id_ok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_shader_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_sys_ne_placement ; 
 int /*<<< orphan*/  vmw_sys_placement ; 

int vmw_compat_shader_add(struct vmw_private *dev_priv,
			  struct vmw_cmdbuf_res_manager *man,
			  u32 user_key, const void *bytecode,
			  SVGA3dShaderType shader_type,
			  size_t size,
			  struct list_head *list)
{
	struct ttm_operation_ctx ctx = { false, true };
	struct vmw_buffer_object *buf;
	struct ttm_bo_kmap_obj map;
	bool is_iomem;
	int ret;
	struct vmw_resource *res;

	if (!vmw_shader_id_ok(user_key, shader_type))
		return -EINVAL;

	/* Allocate and pin a DMA buffer */
	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (unlikely(!buf))
		return -ENOMEM;

	ret = vmw_bo_init(dev_priv, buf, size, &vmw_sys_ne_placement,
			      true, vmw_bo_bo_free);
	if (unlikely(ret != 0))
		goto out;

	ret = ttm_bo_reserve(&buf->base, false, true, NULL);
	if (unlikely(ret != 0))
		goto no_reserve;

	/* Map and copy shader bytecode. */
	ret = ttm_bo_kmap(&buf->base, 0, PAGE_ALIGN(size) >> PAGE_SHIFT,
			  &map);
	if (unlikely(ret != 0)) {
		ttm_bo_unreserve(&buf->base);
		goto no_reserve;
	}

	memcpy(ttm_kmap_obj_virtual(&map, &is_iomem), bytecode, size);
	WARN_ON(is_iomem);

	ttm_bo_kunmap(&map);
	ret = ttm_bo_validate(&buf->base, &vmw_sys_placement, &ctx);
	WARN_ON(ret != 0);
	ttm_bo_unreserve(&buf->base);

	res = vmw_shader_alloc(dev_priv, buf, size, 0, shader_type);
	if (unlikely(ret != 0))
		goto no_reserve;

	ret = vmw_cmdbuf_res_add(man, vmw_cmdbuf_res_shader,
				 vmw_shader_key(user_key, shader_type),
				 res, list);
	vmw_resource_unreference(&res);
no_reserve:
	vmw_bo_unreference(&buf);
out:
	return ret;
}