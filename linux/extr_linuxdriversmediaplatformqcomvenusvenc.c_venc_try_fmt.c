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
struct venus_inst {int dummy; } ;
struct v4l2_format {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct venus_inst* to_inst (struct file*) ; 
 int /*<<< orphan*/  venc_try_fmt_common (struct venus_inst*,struct v4l2_format*) ; 

__attribute__((used)) static int venc_try_fmt(struct file *file, void *fh, struct v4l2_format *f)
{
	struct venus_inst *inst = to_inst(file);

	venc_try_fmt_common(inst, f);

	return 0;
}