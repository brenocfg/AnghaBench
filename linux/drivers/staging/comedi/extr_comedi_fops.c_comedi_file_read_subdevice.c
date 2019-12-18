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
struct file {struct comedi_file* private_data; } ;
struct comedi_subdevice {int dummy; } ;
struct comedi_file {int /*<<< orphan*/  read_subdev; } ;

/* Variables and functions */
 struct comedi_subdevice* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comedi_file_check (struct file*) ; 

__attribute__((used)) static struct comedi_subdevice *comedi_file_read_subdevice(struct file *file)
{
	struct comedi_file *cfp = file->private_data;

	comedi_file_check(file);
	return READ_ONCE(cfp->read_subdev);
}