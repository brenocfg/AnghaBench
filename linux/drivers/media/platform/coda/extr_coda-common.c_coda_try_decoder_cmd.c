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
struct v4l2_decoder_cmd {int dummy; } ;
struct file {int dummy; } ;
struct coda_ctx {scalar_t__ inst_type; } ;

/* Variables and functions */
 scalar_t__ CODA_INST_DECODER ; 
 int ENOTTY ; 
 struct coda_ctx* fh_to_ctx (void*) ; 
 int v4l2_m2m_ioctl_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 

__attribute__((used)) static int coda_try_decoder_cmd(struct file *file, void *fh,
				struct v4l2_decoder_cmd *dc)
{
	struct coda_ctx *ctx = fh_to_ctx(fh);

	if (ctx->inst_type != CODA_INST_DECODER)
		return -ENOTTY;

	return v4l2_m2m_ioctl_try_decoder_cmd(file, fh, dc);
}