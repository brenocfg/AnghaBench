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
struct inode {int /*<<< orphan*/  i_private; } ;
struct file {struct debug_buffer* private_data; } ;
struct debug_buffer {int alloc_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int PAGE_SIZE ; 
 struct debug_buffer* alloc_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_periodic_buffer ; 

__attribute__((used)) static int debug_periodic_open(struct inode *inode, struct file *file)
{
	struct debug_buffer *buf;

	buf = alloc_buffer(inode->i_private, fill_periodic_buffer);
	if (!buf)
		return -ENOMEM;

	buf->alloc_size = (sizeof(void *) == 4 ? 6 : 8)*PAGE_SIZE;
	file->private_data = buf;
	return 0;
}