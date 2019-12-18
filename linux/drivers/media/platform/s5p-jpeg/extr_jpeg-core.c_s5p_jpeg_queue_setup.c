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
struct s5p_jpeg_q_data {unsigned int size; } ;
struct s5p_jpeg_ctx {scalar_t__ mode; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 scalar_t__ S5P_JPEG_DECODE ; 
 struct s5p_jpeg_q_data* get_q_data (struct s5p_jpeg_ctx*,int /*<<< orphan*/ ) ; 
 struct s5p_jpeg_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int s5p_jpeg_queue_setup(struct vb2_queue *vq,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct s5p_jpeg_ctx *ctx = vb2_get_drv_priv(vq);
	struct s5p_jpeg_q_data *q_data = NULL;
	unsigned int size, count = *nbuffers;

	q_data = get_q_data(ctx, vq->type);
	BUG_ON(q_data == NULL);

	size = q_data->size;

	/*
	 * header is parsed during decoding and parsed information stored
	 * in the context so we do not allow another buffer to overwrite it
	 */
	if (ctx->mode == S5P_JPEG_DECODE)
		count = 1;

	*nbuffers = count;
	*nplanes = 1;
	sizes[0] = size;

	return 0;
}