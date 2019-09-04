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
struct vpfe_device {int /*<<< orphan*/  v4l2_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int vpfe_get_app_input_index (struct vpfe_device*,unsigned int*) ; 

__attribute__((used)) static int vpfe_g_input(struct file *file, void *priv, unsigned int *index)
{
	struct vpfe_device *vpfe_dev = video_drvdata(file);

	v4l2_dbg(1, debug, &vpfe_dev->v4l2_dev, "vpfe_g_input\n");

	return vpfe_get_app_input_index(vpfe_dev, index);
}