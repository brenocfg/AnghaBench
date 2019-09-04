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
struct g2d_data {int dummy; } ;
struct g2d_buf_info {int map_nr; int* reg_types; scalar_t__* types; int /*<<< orphan*/ ** obj; struct g2d_buf_desc* descs; } ;
struct g2d_cmdlist_node {struct g2d_buf_info buf_info; } ;
struct g2d_buf_desc {int dummy; } ;
struct drm_file {int dummy; } ;
typedef  enum g2d_reg_type { ____Placeholder_g2d_reg_type } g2d_reg_type ;

/* Variables and functions */
 scalar_t__ BUF_TYPE_GEM ; 
 int REG_TYPE_NONE ; 
 int /*<<< orphan*/  exynos_drm_gem_put (void*) ; 
 int /*<<< orphan*/  g2d_userptr_put_dma_addr (struct g2d_data*,void*,int) ; 
 int /*<<< orphan*/  memset (struct g2d_buf_desc*,int,int) ; 

__attribute__((used)) static void g2d_unmap_cmdlist_gem(struct g2d_data *g2d,
				  struct g2d_cmdlist_node *node,
				  struct drm_file *filp)
{
	struct g2d_buf_info *buf_info = &node->buf_info;
	int i;

	for (i = 0; i < buf_info->map_nr; i++) {
		struct g2d_buf_desc *buf_desc;
		enum g2d_reg_type reg_type;
		void *obj;

		reg_type = buf_info->reg_types[i];

		buf_desc = &buf_info->descs[reg_type];
		obj = buf_info->obj[reg_type];

		if (buf_info->types[reg_type] == BUF_TYPE_GEM)
			exynos_drm_gem_put(obj);
		else
			g2d_userptr_put_dma_addr(g2d, obj, false);

		buf_info->reg_types[i] = REG_TYPE_NONE;
		buf_info->obj[reg_type] = NULL;
		buf_info->types[reg_type] = 0;
		memset(buf_desc, 0x00, sizeof(*buf_desc));
	}

	buf_info->map_nr = 0;
}