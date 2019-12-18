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
struct pxp_q_data {scalar_t__ sequence; } ;
struct pxp_ctx {int dummy; } ;

/* Variables and functions */
 struct pxp_q_data* get_q_data (struct pxp_ctx*,int /*<<< orphan*/ ) ; 
 struct pxp_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int pxp_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct pxp_ctx *ctx = vb2_get_drv_priv(q);
	struct pxp_q_data *q_data = get_q_data(ctx, q->type);

	q_data->sequence = 0;
	return 0;
}