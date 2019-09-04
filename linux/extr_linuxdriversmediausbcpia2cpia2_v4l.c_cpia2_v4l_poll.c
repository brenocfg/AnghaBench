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
struct poll_table_struct {int dummy; } ;
struct file {int dummy; } ;
struct camera_data {int /*<<< orphan*/  v4l2_lock; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpia2_poll (struct camera_data*,struct file*,struct poll_table_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct camera_data* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t cpia2_v4l_poll(struct file *filp, struct poll_table_struct *wait)
{
	struct camera_data *cam = video_drvdata(filp);
	__poll_t res;

	mutex_lock(&cam->v4l2_lock);
	res = cpia2_poll(cam, filp, wait);
	mutex_unlock(&cam->v4l2_lock);
	return res;
}