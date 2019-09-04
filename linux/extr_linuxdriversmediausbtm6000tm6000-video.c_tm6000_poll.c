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
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {int /*<<< orphan*/  lock; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct tm6000_fh* private_data; } ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  __tm6000_poll (struct file*,struct poll_table_struct*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t tm6000_poll(struct file *file, struct poll_table_struct *wait)
{
	struct tm6000_fh *fh = file->private_data;
	struct tm6000_core *dev = fh->dev;
	__poll_t res;

	mutex_lock(&dev->lock);
	res = __tm6000_poll(file, wait);
	mutex_unlock(&dev->lock);
	return res;
}