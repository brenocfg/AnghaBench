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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct file {int dummy; } ;
struct em28xx {TYPE_1__* v4l2; } ;
struct TYPE_2__ {int /*<<< orphan*/  norm; } ;

/* Variables and functions */
 struct em28xx* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *norm)
{
	struct em28xx *dev = video_drvdata(file);

	*norm = dev->v4l2->norm;

	return 0;
}