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
struct inode {scalar_t__ i_private; } ;
struct ibmasmfs_command_data {scalar_t__ sp; int /*<<< orphan*/ * command; } ;
struct file {struct ibmasmfs_command_data* private_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ibmasmfs_command_data* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int command_file_open(struct inode *inode, struct file *file)
{
	struct ibmasmfs_command_data *command_data;

	if (!inode->i_private)
		return -ENODEV;

	command_data = kmalloc(sizeof(struct ibmasmfs_command_data), GFP_KERNEL);
	if (!command_data)
		return -ENOMEM;

	command_data->command = NULL;
	command_data->sp = inode->i_private;
	file->private_data = command_data;
	return 0;
}