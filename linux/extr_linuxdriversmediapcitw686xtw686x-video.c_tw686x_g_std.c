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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct tw686x_video_channel {int /*<<< orphan*/  video_standard; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct tw686x_video_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw686x_g_std(struct file *file, void *priv, v4l2_std_id *id)
{
	struct tw686x_video_channel *vc = video_drvdata(file);

	*id = vc->video_standard;
	return 0;
}