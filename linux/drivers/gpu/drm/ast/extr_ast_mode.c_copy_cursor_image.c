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
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
typedef  int s32 ;

/* Variables and functions */
 int AST_MAX_HWC_HEIGHT ; 
 int AST_MAX_HWC_WIDTH ; 
 int /*<<< orphan*/  writel (int,int*) ; 
 int /*<<< orphan*/  writew (scalar_t__,int*) ; 

__attribute__((used)) static u32 copy_cursor_image(u8 *src, u8 *dst, int width, int height)
{
	union {
		u32 ul;
		u8 b[4];
	} srcdata32[2], data32;
	union {
		u16 us;
		u8 b[2];
	} data16;
	u32 csum = 0;
	s32 alpha_dst_delta, last_alpha_dst_delta;
	u8 *srcxor, *dstxor;
	int i, j;
	u32 per_pixel_copy, two_pixel_copy;

	alpha_dst_delta = AST_MAX_HWC_WIDTH << 1;
	last_alpha_dst_delta = alpha_dst_delta - (width << 1);

	srcxor = src;
	dstxor = (u8 *)dst + last_alpha_dst_delta + (AST_MAX_HWC_HEIGHT - height) * alpha_dst_delta;
	per_pixel_copy = width & 1;
	two_pixel_copy = width >> 1;

	for (j = 0; j < height; j++) {
		for (i = 0; i < two_pixel_copy; i++) {
			srcdata32[0].ul = *((u32 *)srcxor) & 0xf0f0f0f0;
			srcdata32[1].ul = *((u32 *)(srcxor + 4)) & 0xf0f0f0f0;
			data32.b[0] = srcdata32[0].b[1] | (srcdata32[0].b[0] >> 4);
			data32.b[1] = srcdata32[0].b[3] | (srcdata32[0].b[2] >> 4);
			data32.b[2] = srcdata32[1].b[1] | (srcdata32[1].b[0] >> 4);
			data32.b[3] = srcdata32[1].b[3] | (srcdata32[1].b[2] >> 4);

			writel(data32.ul, dstxor);
			csum += data32.ul;

			dstxor += 4;
			srcxor += 8;

		}

		for (i = 0; i < per_pixel_copy; i++) {
			srcdata32[0].ul = *((u32 *)srcxor) & 0xf0f0f0f0;
			data16.b[0] = srcdata32[0].b[1] | (srcdata32[0].b[0] >> 4);
			data16.b[1] = srcdata32[0].b[3] | (srcdata32[0].b[2] >> 4);
			writew(data16.us, dstxor);
			csum += (u32)data16.us;

			dstxor += 2;
			srcxor += 4;
		}
		dstxor += last_alpha_dst_delta;
	}
	return csum;
}