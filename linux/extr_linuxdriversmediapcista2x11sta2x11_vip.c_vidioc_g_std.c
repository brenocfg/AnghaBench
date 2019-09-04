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
struct sta2x11_vip {int /*<<< orphan*/  std; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct sta2x11_vip* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *std)
{
	struct sta2x11_vip *vip = video_drvdata(file);

	*std = vip->std;
	return 0;
}