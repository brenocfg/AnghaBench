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
struct salinfo_data {int open; scalar_t__ state; int /*<<< orphan*/  type; int /*<<< orphan*/  log_buffer; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EBUSY ; 
 int ENOMEM ; 
 int EPERM ; 
 struct salinfo_data* PDE_DATA (struct inode*) ; 
 scalar_t__ STATE_NO_DATA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_lock ; 
 int /*<<< orphan*/  ia64_sal_get_state_info_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
salinfo_log_open(struct inode *inode, struct file *file)
{
	struct salinfo_data *data = PDE_DATA(inode);

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	spin_lock(&data_lock);
	if (data->open) {
		spin_unlock(&data_lock);
		return -EBUSY;
	}
	data->open = 1;
	spin_unlock(&data_lock);

	if (data->state == STATE_NO_DATA &&
	    !(data->log_buffer = vmalloc(ia64_sal_get_state_info_size(data->type)))) {
		data->open = 0;
		return -ENOMEM;
	}

	return 0;
}