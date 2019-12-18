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
struct inode {int dummy; } ;
struct file {int f_flags; struct dvb_device* private_data; } ;
struct dvb_device {struct ddb_output* priv; } ;
struct ddb_output {TYPE_1__* port; } ;
struct ddb_input {scalar_t__ redi; scalar_t__ redo; } ;
struct TYPE_2__ {struct ddb_input** input; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int O_ACCMODE ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  ddb_input_start (struct ddb_input*) ; 
 int /*<<< orphan*/  ddb_output_start (struct ddb_output*) ; 
 int dvb_generic_open (struct inode*,struct file*) ; 

__attribute__((used)) static int ts_open(struct inode *inode, struct file *file)
{
	int err;
	struct dvb_device *dvbdev = file->private_data;
	struct ddb_output *output = NULL;
	struct ddb_input *input = NULL;

	if (dvbdev) {
		output = dvbdev->priv;
		input = output->port->input[0];
	}

	if ((file->f_flags & O_ACCMODE) == O_RDONLY) {
		if (!input)
			return -EINVAL;
		if (input->redo || input->redi)
			return -EBUSY;
	} else if ((file->f_flags & O_ACCMODE) == O_WRONLY) {
		if (!output)
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	err = dvb_generic_open(inode, file);
	if (err < 0)
		return err;
	if ((file->f_flags & O_ACCMODE) == O_RDONLY)
		ddb_input_start(input);
	else if ((file->f_flags & O_ACCMODE) == O_WRONLY)
		ddb_output_start(output);
	return err;
}