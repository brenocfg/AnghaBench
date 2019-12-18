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
struct cal_ctx {unsigned int input; } ;

/* Variables and functions */
 struct cal_ctx* video_drvdata (struct file*) ; 

__attribute__((used)) static int cal_g_input(struct file *file, void *priv, unsigned int *i)
{
	struct cal_ctx *ctx = video_drvdata(file);

	*i = ctx->input;
	return 0;
}