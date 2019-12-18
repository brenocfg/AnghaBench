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
struct hso_serial {int dummy; } ;

/* Variables and functions */
 struct hso_serial* dev2ser (scalar_t__) ; 
 scalar_t__* serial_table ; 
 int /*<<< orphan*/  serial_table_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct hso_serial *get_serial_by_index(unsigned index)
{
	struct hso_serial *serial = NULL;
	unsigned long flags;

	spin_lock_irqsave(&serial_table_lock, flags);
	if (serial_table[index])
		serial = dev2ser(serial_table[index]);
	spin_unlock_irqrestore(&serial_table_lock, flags);

	return serial;
}