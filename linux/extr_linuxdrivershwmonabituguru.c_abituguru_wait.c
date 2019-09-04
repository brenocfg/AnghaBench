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
 scalar_t__ ABIT_UGURU_DATA ; 
 int ABIT_UGURU_WAIT_TIMEOUT ; 
 int ABIT_UGURU_WAIT_TIMEOUT_SLEEP ; 
 int EBUSY ; 
 scalar_t__ inb_p (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int abituguru_wait(struct abituguru_data *data, u8 state)
{
	int timeout = ABIT_UGURU_WAIT_TIMEOUT;

	while (inb_p(data->addr + ABIT_UGURU_DATA) != state) {
		timeout--;
		if (timeout == 0)
			return -EBUSY;
		/*
		 * sleep a bit before our last few tries, see the comment on
		 * this where ABIT_UGURU_WAIT_TIMEOUT_SLEEP is defined.
		 */
		if (timeout <= ABIT_UGURU_WAIT_TIMEOUT_SLEEP)
			msleep(0);
	}
	return 0;
}