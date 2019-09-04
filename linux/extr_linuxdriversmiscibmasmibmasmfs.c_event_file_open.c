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
struct service_processor {int dummy; } ;
struct inode {struct service_processor* i_private; } ;
struct ibmasmfs_event_data {scalar_t__ active; struct service_processor* sp; int /*<<< orphan*/  reader; } ;
struct file {struct ibmasmfs_event_data* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ibmasm_event_reader_register (struct service_processor*,int /*<<< orphan*/ *) ; 
 struct ibmasmfs_event_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int event_file_open(struct inode *inode, struct file *file)
{
	struct ibmasmfs_event_data *event_data;
	struct service_processor *sp;

	if (!inode->i_private)
		return -ENODEV;

	sp = inode->i_private;

	event_data = kmalloc(sizeof(struct ibmasmfs_event_data), GFP_KERNEL);
	if (!event_data)
		return -ENOMEM;

	ibmasm_event_reader_register(sp, &event_data->reader);

	event_data->sp = sp;
	event_data->active = 0;
	file->private_data = event_data;
	return 0;
}