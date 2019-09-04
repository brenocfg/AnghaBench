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
struct file {int dummy; } ;

/* Variables and functions */
 int single_open (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiidebug_drm_show ; 

__attribute__((used)) static int wiidebug_drm_open(struct inode *i, struct file *f)
{
	return single_open(f, wiidebug_drm_show, i->i_private);
}