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
typedef  int u16 ;

/* Variables and functions */
 int I8254_CMD_READBACK ; 
 int /*<<< orphan*/  I8254_PORT_CONTROL ; 
 int /*<<< orphan*/  I8254_PORT_COUNTER0 ; 
 int I8254_SELECT_COUNTER0 ; 
 int I8254_STATUS_NOTREADY ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 i8254(void)
{
	u16 status, timer;

	do {
		outb(I8254_CMD_READBACK | I8254_SELECT_COUNTER0,
		     I8254_PORT_CONTROL);
		status = inb(I8254_PORT_COUNTER0);
		timer  = inb(I8254_PORT_COUNTER0);
		timer |= inb(I8254_PORT_COUNTER0) << 8;
	} while (status & I8254_STATUS_NOTREADY);

	return timer;
}