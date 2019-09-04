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
struct file {int dummy; } ;
struct dvb_vb2_ctx {int /*<<< orphan*/  vb_q; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_core_poll (int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 

__poll_t dvb_vb2_poll(struct dvb_vb2_ctx *ctx, struct file *file,
		      poll_table *wait)
{
	dprintk(3, "[%s]\n", ctx->name);
	return vb2_core_poll(&ctx->vb_q, file, wait);
}