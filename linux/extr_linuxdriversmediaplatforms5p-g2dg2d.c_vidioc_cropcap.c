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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_cropcap {TYPE_1__ bounds; TYPE_1__ defrect; int /*<<< orphan*/  type; } ;
struct g2d_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct g2d_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct g2d_frame*) ; 
 int PTR_ERR (struct g2d_frame*) ; 
 struct g2d_frame* get_frame (struct g2d_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_cropcap(struct file *file, void *priv,
					struct v4l2_cropcap *cr)
{
	struct g2d_ctx *ctx = priv;
	struct g2d_frame *f;

	f = get_frame(ctx, cr->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	cr->bounds.left		= 0;
	cr->bounds.top		= 0;
	cr->bounds.width	= f->width;
	cr->bounds.height	= f->height;
	cr->defrect		= cr->bounds;
	return 0;
}