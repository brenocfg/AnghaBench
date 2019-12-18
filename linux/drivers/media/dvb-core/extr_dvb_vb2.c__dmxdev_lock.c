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
struct vb2_queue {int dummy; } ;
struct dvb_vb2_ctx {int /*<<< orphan*/  name; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct dvb_vb2_ctx* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void _dmxdev_lock(struct vb2_queue *vq)
{
	struct dvb_vb2_ctx *ctx = vb2_get_drv_priv(vq);

	mutex_lock(&ctx->mutex);
	dprintk(3, "[%s]\n", ctx->name);
}