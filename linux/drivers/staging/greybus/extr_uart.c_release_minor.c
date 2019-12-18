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
struct gb_tty {int minor; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_lock ; 
 int /*<<< orphan*/  tty_minors ; 

__attribute__((used)) static void release_minor(struct gb_tty *gb_tty)
{
	int minor = gb_tty->minor;

	gb_tty->minor = 0;	/* Maybe should use an invalid value instead */
	mutex_lock(&table_lock);
	idr_remove(&tty_minors, minor);
	mutex_unlock(&table_lock);
}