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
struct comedi_device {unsigned int minor; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct comedi_device** comedi_board_minor_table ; 
 int /*<<< orphan*/  comedi_board_minor_table_lock ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool comedi_clear_board_dev(struct comedi_device *dev)
{
	unsigned int i = dev->minor;
	bool cleared = false;

	lockdep_assert_held(&dev->mutex);
	mutex_lock(&comedi_board_minor_table_lock);
	if (dev == comedi_board_minor_table[i]) {
		comedi_board_minor_table[i] = NULL;
		cleared = true;
	}
	mutex_unlock(&comedi_board_minor_table_lock);
	return cleared;
}