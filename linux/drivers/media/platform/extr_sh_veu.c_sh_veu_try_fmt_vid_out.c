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
struct v4l2_format {int dummy; } ;
struct sh_veu_format {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct sh_veu_format* sh_veu_find_fmt (struct v4l2_format*) ; 
 int sh_veu_try_fmt (struct v4l2_format*,struct sh_veu_format const*) ; 

__attribute__((used)) static int sh_veu_try_fmt_vid_out(struct file *file, void *priv,
				  struct v4l2_format *f)
{
	const struct sh_veu_format *fmt;

	fmt = sh_veu_find_fmt(f);

	return sh_veu_try_fmt(f, fmt);
}