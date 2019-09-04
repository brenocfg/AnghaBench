#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct hwicap_drvdata {int write_buffer_in_use; int /*<<< orphan*/  sem; scalar_t__ is_open; scalar_t__* write_buffer; TYPE_1__* config; } ;
struct file {struct hwicap_drvdata* private_data; } ;
struct TYPE_2__ {int (* set_configuration ) (struct hwicap_drvdata*,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int hwicap_command_desync (struct hwicap_drvdata*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct hwicap_drvdata*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hwicap_release(struct inode *inode, struct file *file)
{
	struct hwicap_drvdata *drvdata = file->private_data;
	int i;
	int status = 0;

	mutex_lock(&drvdata->sem);

	if (drvdata->write_buffer_in_use) {
		/* Flush write buffer. */
		for (i = drvdata->write_buffer_in_use; i < 4; i++)
			drvdata->write_buffer[i] = 0;

		status = drvdata->config->set_configuration(drvdata,
				(u32 *) drvdata->write_buffer, 1);
		if (status)
			goto error;
	}

	status = hwicap_command_desync(drvdata);
	if (status)
		goto error;

 error:
	drvdata->is_open = 0;
	mutex_unlock(&drvdata->sem);
	return status;
}