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
struct file {struct bfad_debug_info* private_data; } ;
struct bfad_debug_info {int /*<<< orphan*/  buffer_len; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  fixed_size_llseek (struct file*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t
bfad_debugfs_lseek(struct file *file, loff_t offset, int orig)
{
	struct bfad_debug_info *debug = file->private_data;
	return fixed_size_llseek(file, offset, orig,
				debug->buffer_len);
}