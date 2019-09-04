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
struct v4l2_buffer {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;
struct coda_ctx {TYPE_1__ fh; } ;

/* Variables and functions */
 struct coda_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_qbuf (struct file*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int coda_qbuf(struct file *file, void *priv,
		     struct v4l2_buffer *buf)
{
	struct coda_ctx *ctx = fh_to_ctx(priv);

	return v4l2_m2m_qbuf(file, ctx->fh.m2m_ctx, buf);
}