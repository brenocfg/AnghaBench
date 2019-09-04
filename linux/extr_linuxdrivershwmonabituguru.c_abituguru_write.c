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
 int /*<<< orphan*/  ABIT_UGURU_MAX_RETRIES ; 
 int ABIT_UGURU_READY_TIMEOUT ; 
 int /*<<< orphan*/  ABIT_UGURU_STATUS_READ ; 
 int /*<<< orphan*/  ABIT_UGURU_STATUS_WRITE ; 
 int EIO ; 
 int /*<<< orphan*/  abituguru_ready (struct abituguru_data*) ; 
 int abituguru_send_address (struct abituguru_data*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ abituguru_wait (struct abituguru_data*,int /*<<< orphan*/ ) ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int abituguru_write(struct abituguru_data *data,
	u8 bank_addr, u8 sensor_addr, u8 *buf, int count)
{
	/*
	 * We use the ready timeout as we have to wait for 0xAC just like the
	 * ready function
	 */
	int i, timeout = ABIT_UGURU_READY_TIMEOUT;

	/* Send the address */
	i = abituguru_send_address(data, bank_addr, sensor_addr,
		ABIT_UGURU_MAX_RETRIES);
	if (i)
		return i;

	/* And write the data */
	for (i = 0; i < count; i++) {
		if (abituguru_wait(data, ABIT_UGURU_STATUS_WRITE)) {
			ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for "
				"write state (bank: %d, sensor: %d)\n",
				(int)bank_addr, (int)sensor_addr);
			break;
		}
		outb(buf[i], data->addr + ABIT_UGURU_CMD);
	}

	/*
	 * Now we need to wait till the chip is ready to be read again,
	 * so that we can read 0xAC as confirmation that our write has
	 * succeeded.
	 */
	if (abituguru_wait(data, ABIT_UGURU_STATUS_READ)) {
		ABIT_UGURU_DEBUG(1, "timeout exceeded waiting for read state "
			"after write (bank: %d, sensor: %d)\n", (int)bank_addr,
			(int)sensor_addr);
		return -EIO;
	}

	/* Cmd port MUST be read now and should contain 0xAC */
	while (inb_p(data->addr + ABIT_UGURU_CMD) != 0xAC) {
		timeout--;
		if (timeout == 0) {
			ABIT_UGURU_DEBUG(1, "CMD reg does not hold 0xAC after "
				"write (bank: %d, sensor: %d)\n",
				(int)bank_addr, (int)sensor_addr);
			return -EIO;
		}
		msleep(0);
	}

	/* Last put the chip back in ready state */
	abituguru_ready(data);

	return i;
}