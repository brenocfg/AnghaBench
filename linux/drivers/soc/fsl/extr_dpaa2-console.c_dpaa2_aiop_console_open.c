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
 int /*<<< orphan*/  AIOP_BUFFER_OFFSET ; 
 int /*<<< orphan*/  AIOP_BUFFER_SIZE ; 
 int /*<<< orphan*/  AIOP_OFFSET_DELTA ; 
 int /*<<< orphan*/  MAGIC_AIOP ; 
 int dpaa2_generic_console_open (struct inode*,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa2_aiop_console_open(struct inode *node, struct file *fp)
{
	return dpaa2_generic_console_open(node, fp,
					  AIOP_BUFFER_OFFSET, AIOP_BUFFER_SIZE,
					  MAGIC_AIOP, AIOP_OFFSET_DELTA);
}