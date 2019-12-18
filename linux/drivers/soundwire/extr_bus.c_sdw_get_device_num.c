#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdw_slave {TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  assigned; } ;

/* Variables and functions */
 int ENODEV ; 
 int SDW_MAX_DEVICES ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_get_device_num(struct sdw_slave *slave)
{
	int bit;

	bit = find_first_zero_bit(slave->bus->assigned, SDW_MAX_DEVICES);
	if (bit == SDW_MAX_DEVICES) {
		bit = -ENODEV;
		goto err;
	}

	/*
	 * Do not update dev_num in Slave data structure here,
	 * Update once program dev_num is successful
	 */
	set_bit(bit, slave->bus->assigned);

err:
	return bit;
}