#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int x1; int y1; } ;
struct TYPE_4__ {int x1; int y1; } ;
struct vkms_composer {int offset; int pitch; int cpp; TYPE_2__ dst; TYPE_1__ src; } ;

/* Variables and functions */
 int drm_rect_height (TYPE_2__*) ; 
 int drm_rect_width (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static void blend(void *vaddr_dst, void *vaddr_src,
		  struct vkms_composer *dest_composer,
		  struct vkms_composer *src_composer)
{
	int i, j, j_dst, i_dst;
	int offset_src, offset_dst;

	int x_src = src_composer->src.x1 >> 16;
	int y_src = src_composer->src.y1 >> 16;

	int x_dst = src_composer->dst.x1;
	int y_dst = src_composer->dst.y1;
	int h_dst = drm_rect_height(&src_composer->dst);
	int w_dst = drm_rect_width(&src_composer->dst);

	int y_limit = y_src + h_dst;
	int x_limit = x_src + w_dst;

	for (i = y_src, i_dst = y_dst; i < y_limit; ++i) {
		for (j = x_src, j_dst = x_dst; j < x_limit; ++j) {
			offset_dst = dest_composer->offset
				     + (i_dst * dest_composer->pitch)
				     + (j_dst++ * dest_composer->cpp);
			offset_src = src_composer->offset
				     + (i * src_composer->pitch)
				     + (j * src_composer->cpp);

			memcpy(vaddr_dst + offset_dst,
			       vaddr_src + offset_src, sizeof(u32));
		}
		i_dst++;
	}
}