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
struct go7007 {int /*<<< orphan*/  std; int /*<<< orphan*/  vidq; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int go7007_s_std (struct go7007*) ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct go7007* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_s_std(struct file *file, void *priv, v4l2_std_id std)
{
	struct go7007 *go = video_drvdata(file);

	if (vb2_is_busy(&go->vidq))
		return -EBUSY;

	go->std = std;

	return go7007_s_std(go);
}