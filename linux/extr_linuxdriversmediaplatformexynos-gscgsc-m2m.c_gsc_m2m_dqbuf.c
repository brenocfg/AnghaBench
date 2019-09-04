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
struct v4l2_buffer {int dummy; } ;
struct gsc_ctx {int /*<<< orphan*/  m2m_ctx; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct gsc_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_dqbuf (struct file*,int /*<<< orphan*/ ,struct v4l2_buffer*) ; 

__attribute__((used)) static int gsc_m2m_dqbuf(struct file *file, void *fh,
			   struct v4l2_buffer *buf)
{
	struct gsc_ctx *ctx = fh_to_ctx(fh);
	return v4l2_m2m_dqbuf(file, ctx->m2m_ctx, buf);
}