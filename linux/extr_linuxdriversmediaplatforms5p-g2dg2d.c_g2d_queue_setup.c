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
struct vb2_queue {int /*<<< orphan*/  type; } ;
struct g2d_frame {unsigned int size; } ;
struct g2d_ctx {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct g2d_frame*) ; 
 int PTR_ERR (struct g2d_frame*) ; 
 struct g2d_frame* get_frame (struct g2d_ctx*,int /*<<< orphan*/ ) ; 
 struct g2d_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int g2d_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct g2d_ctx *ctx = vb2_get_drv_priv(vq);
	struct g2d_frame *f = get_frame(ctx, vq->type);

	if (IS_ERR(f))
		return PTR_ERR(f);

	sizes[0] = f->size;
	*nplanes = 1;

	if (*nbuffers == 0)
		*nbuffers = 1;

	return 0;
}