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
struct tty_struct {int /*<<< orphan*/  files_lock; } ;
struct tty_file_private {int /*<<< orphan*/  list; struct tty_struct* tty; } ;
struct file {struct tty_file_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_free_file (struct file*) ; 

__attribute__((used)) static void tty_del_file(struct file *file)
{
	struct tty_file_private *priv = file->private_data;
	struct tty_struct *tty = priv->tty;

	spin_lock(&tty->files_lock);
	list_del(&priv->list);
	spin_unlock(&tty->files_lock);
	tty_free_file(file);
}