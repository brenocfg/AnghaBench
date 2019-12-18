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
 int /*<<< orphan*/  global_driver ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uctrl_get_event_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uctrl_get_external_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uctrl_mutex ; 

__attribute__((used)) static int
uctrl_open(struct inode *inode, struct file *file)
{
	mutex_lock(&uctrl_mutex);
	uctrl_get_event_status(global_driver);
	uctrl_get_external_status(global_driver);
	mutex_unlock(&uctrl_mutex);
	return 0;
}