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
struct s2255_vc {int /*<<< orphan*/  std; } ;
struct file {int dummy; } ;

/* Variables and functions */
 struct s2255_vc* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_g_std(struct file *file, void *priv, v4l2_std_id *i)
{
	struct s2255_vc *vc = video_drvdata(file);

	*i = vc->std;
	return 0;
}