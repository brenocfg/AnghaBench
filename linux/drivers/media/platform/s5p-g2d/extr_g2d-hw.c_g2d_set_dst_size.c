#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct g2d_frame {int stride; int o_height; int o_width; int bottom; int right; TYPE_1__* fmt; } ;
struct g2d_dev {int dummy; } ;
struct TYPE_2__ {int hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_COLOR_MODE_REG ; 
 int /*<<< orphan*/  DST_LEFT_TOP_REG ; 
 int /*<<< orphan*/  DST_RIGHT_BOTTOM_REG ; 
 int /*<<< orphan*/  DST_SELECT_REG ; 
 int /*<<< orphan*/  DST_STRIDE_REG ; 
 int /*<<< orphan*/  w (int,int /*<<< orphan*/ ) ; 

void g2d_set_dst_size(struct g2d_dev *d, struct g2d_frame *f)
{
	u32 n;

	w(0, DST_SELECT_REG);
	w(f->stride & 0xFFFF, DST_STRIDE_REG);

	n = f->o_height & 0xFFF;
	n <<= 16;
	n |= f->o_width & 0xFFF;
	w(n, DST_LEFT_TOP_REG);

	n = f->bottom & 0xFFF;
	n <<= 16;
	n |= f->right & 0xFFF;
	w(n, DST_RIGHT_BOTTOM_REG);

	w(f->fmt->hw, DST_COLOR_MODE_REG);
}