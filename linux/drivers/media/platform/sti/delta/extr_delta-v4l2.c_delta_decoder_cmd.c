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
struct delta_ctx {int dummy; } ;

/* Variables and functions */
 int delta_decoder_stop_cmd (struct delta_ctx*,void*) ; 
 int delta_try_decoder_cmd (struct file*,void*,struct v4l2_decoder_cmd*) ; 
 struct delta_ctx* to_ctx (void*) ; 

__attribute__((used)) static int delta_decoder_cmd(struct file *file, void *fh,
			     struct v4l2_decoder_cmd *cmd)
{
	struct delta_ctx *ctx = to_ctx(fh);
	int ret = 0;

	ret = delta_try_decoder_cmd(file, fh, cmd);
	if (ret)
		return ret;

	return delta_decoder_stop_cmd(ctx, fh);
}