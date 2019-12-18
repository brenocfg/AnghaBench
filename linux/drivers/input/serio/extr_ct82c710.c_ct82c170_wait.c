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

/* Variables and functions */
 int /*<<< orphan*/  CT82C710_DATA ; 
 int CT82C710_DEV_IDLE ; 
 int CT82C710_RX_FULL ; 
 int /*<<< orphan*/  CT82C710_STATUS ; 
 int CT82C710_TX_IDLE ; 
 int inb (int /*<<< orphan*/ ) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ct82c170_wait(void)
{
	int timeout = 60000;

	while ((inb(CT82C710_STATUS) & (CT82C710_RX_FULL | CT82C710_TX_IDLE | CT82C710_DEV_IDLE))
		       != (CT82C710_DEV_IDLE | CT82C710_TX_IDLE) && timeout) {

		if (inb_p(CT82C710_STATUS) & CT82C710_RX_FULL) inb_p(CT82C710_DATA);

		udelay(1);
		timeout--;
	}

	return !timeout;
}