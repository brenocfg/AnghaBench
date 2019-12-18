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
 int /*<<< orphan*/  GB_NUM_MINORS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,struct gb_tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_lock ; 
 int /*<<< orphan*/  tty_minors ; 

__attribute__((used)) static int alloc_minor(struct gb_tty *gb_tty)
{
	int minor;

	mutex_lock(&table_lock);
	minor = idr_alloc(&tty_minors, gb_tty, 0, GB_NUM_MINORS, GFP_KERNEL);
	mutex_unlock(&table_lock);
	if (minor >= 0)
		gb_tty->minor = minor;
	return minor;
}