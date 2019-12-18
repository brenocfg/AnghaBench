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
struct inode {int dummy; } ;
struct ibmasmfs_event_data {int /*<<< orphan*/  reader; int /*<<< orphan*/  sp; } ;
struct file {struct ibmasmfs_event_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibmasm_event_reader_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ibmasmfs_event_data*) ; 

__attribute__((used)) static int event_file_close(struct inode *inode, struct file *file)
{
	struct ibmasmfs_event_data *event_data = file->private_data;

	ibmasm_event_reader_unregister(event_data->sp, &event_data->reader);
	kfree(event_data);
	return 0;
}