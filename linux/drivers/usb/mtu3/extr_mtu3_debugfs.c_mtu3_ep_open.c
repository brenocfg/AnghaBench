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
struct mtu3_file_map {int /*<<< orphan*/  show; int /*<<< orphan*/  name; } ;
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* d_iname; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mtu3_file_map*) ; 
 TYPE_1__* file_dentry (struct file*) ; 
 struct mtu3_file_map* mtu3_ep_files ; 
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int mtu3_ep_open(struct inode *inode, struct file *file)
{
	const char *file_name = file_dentry(file)->d_iname;
	const struct mtu3_file_map *f_map;
	int i;

	for (i = 0; i < ARRAY_SIZE(mtu3_ep_files); i++) {
		f_map = &mtu3_ep_files[i];

		if (strcmp(f_map->name, file_name) == 0)
			break;
	}

	return single_open(file, f_map->show, inode->i_private);
}