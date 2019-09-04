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
struct v4l2_streamparm {int dummy; } ;
struct unicam_device {int /*<<< orphan*/  sensor; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int v4l2_g_parm_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_streamparm*) ; 
 int /*<<< orphan*/  video_devdata (struct file*) ; 
 struct unicam_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int unicam_g_parm(struct file *file, void *fh, struct v4l2_streamparm *a)
{
	struct unicam_device *dev = video_drvdata(file);

	return v4l2_g_parm_cap(video_devdata(file), dev->sensor, a);
}