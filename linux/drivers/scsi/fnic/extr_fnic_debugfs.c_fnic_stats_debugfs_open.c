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
struct stats_debug_info {int buf_size; int /*<<< orphan*/  buffer_len; scalar_t__ debug_buffer; } ;
struct inode {struct fnic* i_private; } ;
struct fnic_stats {int dummy; } ;
struct fnic {struct fnic_stats fnic_stats; } ;
struct file {struct stats_debug_info* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  fnic_get_stats_data (struct stats_debug_info*,struct fnic_stats*) ; 
 int /*<<< orphan*/  kfree (struct stats_debug_info*) ; 
 struct stats_debug_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vmalloc (int) ; 

__attribute__((used)) static int fnic_stats_debugfs_open(struct inode *inode,
					struct file *file)
{
	struct fnic *fnic = inode->i_private;
	struct fnic_stats *fnic_stats = &fnic->fnic_stats;
	struct stats_debug_info *debug;
	int buf_size = 2 * PAGE_SIZE;

	debug = kzalloc(sizeof(struct stats_debug_info), GFP_KERNEL);
	if (!debug)
		return -ENOMEM;

	debug->debug_buffer = vmalloc(buf_size);
	if (!debug->debug_buffer) {
		kfree(debug);
		return -ENOMEM;
	}

	debug->buf_size = buf_size;
	memset((void *)debug->debug_buffer, 0, buf_size);
	debug->buffer_len = fnic_get_stats_data(debug, fnic_stats);

	file->private_data = debug;

	return 0;
}