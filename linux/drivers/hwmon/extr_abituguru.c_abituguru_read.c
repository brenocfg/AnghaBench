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
typedef  scalar_t__ u8 ;
struct abituguru_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ABIT_UGURU_CMD ; 
 int /*<<< orphan*/  ABIT_UGURU_DEBUG (int,char*,int,int) ; 
 int /*<<< orphan*/  ABIT_UGURU_STATUS_READ ; 
 int /*<<< orphan*/  abituguru_ready (struct abituguru_data*) ; 
 int abituguru_send_address (struct abituguru_data*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ abituguru_wait (struct abituguru_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ inb (scalar_t__) ; 

__attribute__((used)) static int abituguru_read(struct abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, u8 *buf, int count, int retries)
{
	int i;

	/* Send the address */
	i = abituguru_send_address(data, bank_addr, sensor_addr, retries);
	if (i)
		return i;

	/* And read the data */
	for (i = 0; i < count; i++) {
		if (abituguru_wait(data, ABIT_UGURU_STATUS_READ)) {
			ABIT_UGURU_DEBUG(retries ? 1 : 3,
				"timeout exceeded waiting for "
				"read state (bank: %d, sensor: %d)\n",
				(int)bank_addr, (int)sensor_addr);
			break;
		}
		buf[i] = inb(data->addr + ABIT_UGURU_CMD);
	}

	/* Last put the chip back in ready state */
	abituguru_ready(data);

	return i;
}