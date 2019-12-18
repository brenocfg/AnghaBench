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
struct ni_board_struct {int device_id; } ;
struct comedi_device {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ni_board_struct*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct ni_board_struct* ni_boards ; 
 int ni_read_eeprom (struct comedi_device*,int) ; 

__attribute__((used)) static const struct ni_board_struct *ni_atmio_probe(struct comedi_device *dev)
{
	int device_id = ni_read_eeprom(dev, 511);
	int i;

	for (i = 0; i < ARRAY_SIZE(ni_boards); i++) {
		const struct ni_board_struct *board = &ni_boards[i];

		if (board->device_id == device_id)
			return board;
	}
	if (device_id == 255)
		dev_err(dev->class_dev, "can't find board\n");
	else if (device_id == 0)
		dev_err(dev->class_dev,
			"EEPROM read error (?) or device not found\n");
	else
		dev_err(dev->class_dev,
			"unknown device ID %d -- contact author\n", device_id);

	return NULL;
}