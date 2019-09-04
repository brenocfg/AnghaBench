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
struct vicodec_ctx {int dummy; } ;
struct v4l2_encoder_cmd {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct vicodec_ctx* file2ctx (struct file*) ; 
 int /*<<< orphan*/  vicodec_mark_last_buf (struct vicodec_ctx*) ; 
 int vicodec_try_encoder_cmd (struct file*,void*,struct v4l2_encoder_cmd*) ; 

__attribute__((used)) static int vicodec_encoder_cmd(struct file *file, void *fh,
			    struct v4l2_encoder_cmd *ec)
{
	struct vicodec_ctx *ctx = file2ctx(file);
	int ret;

	ret = vicodec_try_encoder_cmd(file, fh, ec);
	if (ret < 0)
		return ret;

	vicodec_mark_last_buf(ctx);
	return 0;
}