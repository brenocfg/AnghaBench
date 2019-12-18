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
struct hso_serial {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** serial_table ; 
 int /*<<< orphan*/  serial_table_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_serial_by_index(unsigned index, struct hso_serial *serial)
{
	unsigned long flags;

	spin_lock_irqsave(&serial_table_lock, flags);
	if (serial)
		serial_table[index] = serial->parent;
	else
		serial_table[index] = NULL;
	spin_unlock_irqrestore(&serial_table_lock, flags);
}