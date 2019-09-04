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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  AUXIO_AUX1_LED ; 
 int /*<<< orphan*/  AUXIO_PCIO_LED ; 
 scalar_t__ AUXIO_TYPE_EBUS ; 
 int /*<<< orphan*/  __auxio_set_bit (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ auxio_devtype ; 

void auxio_set_led(int on)
{
	int ebus = auxio_devtype == AUXIO_TYPE_EBUS;
	u8 bit;

	bit = (ebus ? AUXIO_PCIO_LED : AUXIO_AUX1_LED);
	__auxio_set_bit(bit, on, ebus);
}