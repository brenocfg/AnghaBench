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
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; scalar_t__ height; scalar_t__ width; } ;
struct v4l2_crop {TYPE_1__ c; int /*<<< orphan*/  type; } ;
struct g2d_frame {scalar_t__ c_width; scalar_t__ o_width; scalar_t__ right; scalar_t__ c_height; scalar_t__ o_height; scalar_t__ bottom; } ;
struct g2d_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct g2d_frame*) ; 
 int PTR_ERR (struct g2d_frame*) ; 
 struct g2d_frame* get_frame (struct g2d_ctx*,int /*<<< orphan*/ ) ; 
 int vidioc_try_crop (struct file*,void*,struct v4l2_crop const*) ; 

__attribute__((used)) static int vidioc_s_crop(struct file *file, void *prv, const struct v4l2_crop *cr)
{
	struct g2d_ctx *ctx = prv;
	struct g2d_frame *f;
	int ret;

	ret = vidioc_try_crop(file, prv, cr);
	if (ret)
		return ret;
	f = get_frame(ctx, cr->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	f->c_width	= cr->c.width;
	f->c_height	= cr->c.height;
	f->o_width	= cr->c.left;
	f->o_height	= cr->c.top;
	f->bottom	= f->o_height + f->c_height;
	f->right	= f->o_width + f->c_width;
	return 0;
}