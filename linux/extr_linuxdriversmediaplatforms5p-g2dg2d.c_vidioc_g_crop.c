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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_crop {TYPE_1__ c; int /*<<< orphan*/  type; } ;
struct g2d_frame {int /*<<< orphan*/  c_height; int /*<<< orphan*/  c_width; int /*<<< orphan*/  o_width; int /*<<< orphan*/  o_height; } ;
struct g2d_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct g2d_frame*) ; 
 int PTR_ERR (struct g2d_frame*) ; 
 struct g2d_frame* get_frame (struct g2d_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_crop(struct file *file, void *prv, struct v4l2_crop *cr)
{
	struct g2d_ctx *ctx = prv;
	struct g2d_frame *f;

	f = get_frame(ctx, cr->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	cr->c.left	= f->o_height;
	cr->c.top	= f->o_width;
	cr->c.width	= f->c_width;
	cr->c.height	= f->c_height;
	return 0;
}