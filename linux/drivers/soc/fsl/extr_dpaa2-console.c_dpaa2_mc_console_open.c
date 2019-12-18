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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_MC ; 
 int /*<<< orphan*/  MC_BUFFER_OFFSET ; 
 int /*<<< orphan*/  MC_BUFFER_SIZE ; 
 int /*<<< orphan*/  MC_OFFSET_DELTA ; 
 int dpaa2_generic_console_open (struct inode*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa2_mc_console_open(struct inode *node, struct file *fp)
{
	return dpaa2_generic_console_open(node, fp,
					  MC_BUFFER_OFFSET, MC_BUFFER_SIZE,
					  MAGIC_MC, MC_OFFSET_DELTA);
}