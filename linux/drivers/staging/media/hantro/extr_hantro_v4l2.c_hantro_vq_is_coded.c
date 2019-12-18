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
struct hantro_ctx {int dummy; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_OUTPUT (int /*<<< orphan*/ ) ; 
 scalar_t__ hantro_is_encoder_ctx (struct hantro_ctx*) ; 
 struct hantro_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static bool hantro_vq_is_coded(struct vb2_queue *q)
{
	struct hantro_ctx *ctx = vb2_get_drv_priv(q);

	return hantro_is_encoder_ctx(ctx) != V4L2_TYPE_IS_OUTPUT(q->type);
}