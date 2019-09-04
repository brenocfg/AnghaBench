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
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ LOOP_MAJOR ; 
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int is_loop_device(struct file *file)
{
	struct inode *i = file->f_mapping->host;

	return i && S_ISBLK(i->i_mode) && MAJOR(i->i_rdev) == LOOP_MAJOR;
}