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
struct saa7134_dev {int /*<<< orphan*/  lock; } ;
struct saa6588_command {int poll_mask; int /*<<< orphan*/ * event_list; struct file* instance; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  SAA6588_CMD_POLL ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  ioctl ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saa_call_all (struct saa7134_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct saa6588_command*) ; 
 int v4l2_ctrl_poll (struct file*,int /*<<< orphan*/ *) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static __poll_t radio_poll(struct file *file, poll_table *wait)
{
	struct saa7134_dev *dev = video_drvdata(file);
	struct saa6588_command cmd;
	__poll_t rc = v4l2_ctrl_poll(file, wait);

	cmd.instance = file;
	cmd.event_list = wait;
	cmd.poll_mask = 0;
	mutex_lock(&dev->lock);
	saa_call_all(dev, core, ioctl, SAA6588_CMD_POLL, &cmd);
	mutex_unlock(&dev->lock);

	return rc | cmd.poll_mask;
}