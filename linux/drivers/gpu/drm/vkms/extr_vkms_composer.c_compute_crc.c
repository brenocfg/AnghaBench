#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int x1; int y1; } ;
struct vkms_composer {int offset; int pitch; int cpp; TYPE_1__ src; } ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_le (int /*<<< orphan*/ ,void*,int) ; 
 int drm_rect_height (TYPE_1__*) ; 
 int drm_rect_width (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t compute_crc(void *vaddr_out, struct vkms_composer *composer)
{
	int i, j, src_offset;
	int x_src = composer->src.x1 >> 16;
	int y_src = composer->src.y1 >> 16;
	int h_src = drm_rect_height(&composer->src) >> 16;
	int w_src = drm_rect_width(&composer->src) >> 16;
	u32 crc = 0;

	for (i = y_src; i < y_src + h_src; ++i) {
		for (j = x_src; j < x_src + w_src; ++j) {
			src_offset = composer->offset
				     + (i * composer->pitch)
				     + (j * composer->cpp);
			/* XRGB format ignores Alpha channel */
			memset(vaddr_out + src_offset + 24, 0,  8);
			crc = crc32_le(crc, vaddr_out + src_offset,
				       sizeof(u32));
		}
	}

	return crc;
}