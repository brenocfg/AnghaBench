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
struct g2d_data {int /*<<< orphan*/  dev; } ;
struct g2d_buf_desc {scalar_t__ right_x; scalar_t__ stride; scalar_t__ bottom_y; int /*<<< orphan*/  format; scalar_t__ top_y; scalar_t__ left_x; } ;
typedef  enum g2d_reg_type { ____Placeholder_g2d_reg_type } g2d_reg_type ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int G2D_LEN_MAX ; 
 int G2D_LEN_MIN ; 
 int REG_TYPE_DST ; 
 int REG_TYPE_SRC ; 
 unsigned long g2d_get_buf_bpp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool g2d_check_buf_desc_is_valid(struct g2d_data *g2d,
					struct g2d_buf_desc *buf_desc,
					enum g2d_reg_type reg_type,
					unsigned long size)
{
	int width, height;
	unsigned long bpp, last_pos;

	/*
	 * check source and destination buffers only.
	 * so the others are always valid.
	 */
	if (reg_type != REG_TYPE_SRC && reg_type != REG_TYPE_DST)
		return true;

	/* This check also makes sure that right_x > left_x. */
	width = (int)buf_desc->right_x - (int)buf_desc->left_x;
	if (width < G2D_LEN_MIN || width > G2D_LEN_MAX) {
		DRM_DEV_ERROR(g2d->dev, "width[%d] is out of range!\n", width);
		return false;
	}

	/* This check also makes sure that bottom_y > top_y. */
	height = (int)buf_desc->bottom_y - (int)buf_desc->top_y;
	if (height < G2D_LEN_MIN || height > G2D_LEN_MAX) {
		DRM_DEV_ERROR(g2d->dev,
			      "height[%d] is out of range!\n", height);
		return false;
	}

	bpp = g2d_get_buf_bpp(buf_desc->format);

	/* Compute the position of the last byte that the engine accesses. */
	last_pos = ((unsigned long)buf_desc->bottom_y - 1) *
		(unsigned long)buf_desc->stride +
		(unsigned long)buf_desc->right_x * bpp - 1;

	/*
	 * Since right_x > left_x and bottom_y > top_y we already know
	 * that the first_pos < last_pos (first_pos being the position
	 * of the first byte the engine accesses), it just remains to
	 * check if last_pos is smaller then the buffer size.
	 */

	if (last_pos >= size) {
		DRM_DEV_ERROR(g2d->dev, "last engine access position [%lu] "
			      "is out of range [%lu]!\n", last_pos, size);
		return false;
	}

	return true;
}