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
struct inode {struct drbd_connection* i_private; } ;
struct file {int dummy; } ;
struct drbd_connection {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_destroy_connection ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int single_release (struct inode*,struct file*) ; 

__attribute__((used)) static int callback_history_release(struct inode *inode, struct file *file)
{
	struct drbd_connection *connection = inode->i_private;
	kref_put(&connection->kref, drbd_destroy_connection);
	return single_release(inode, file);
}