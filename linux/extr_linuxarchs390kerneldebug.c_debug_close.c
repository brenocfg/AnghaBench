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
struct file {scalar_t__ private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  debug_info_org; scalar_t__ debug_info_snap; } ;
typedef  TYPE_1__ file_private_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug_info_free (scalar_t__) ; 
 int /*<<< orphan*/  debug_info_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static int debug_close(struct inode *inode, struct file *file)
{
	file_private_info_t *p_info;

	p_info = (file_private_info_t *) file->private_data;
	if (p_info->debug_info_snap)
		debug_info_free(p_info->debug_info_snap);
	debug_info_put(p_info->debug_info_org);
	kfree(file->private_data);
	return 0; /* success */
}