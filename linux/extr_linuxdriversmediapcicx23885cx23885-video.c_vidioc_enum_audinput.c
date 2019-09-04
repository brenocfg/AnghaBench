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
struct v4l2_audio {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int cx23885_query_audinput (struct file*,void*,struct v4l2_audio*) ; 

__attribute__((used)) static int vidioc_enum_audinput(struct file *file, void *priv,
				struct v4l2_audio *i)
{
	return cx23885_query_audinput(file, priv, i);
}