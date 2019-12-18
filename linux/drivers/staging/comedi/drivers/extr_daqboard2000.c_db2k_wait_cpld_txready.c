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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int DB2K_CPLD_STATUS_TXREADY ; 
 scalar_t__ DB2K_REG_CPLD_STATUS ; 
 int ETIMEDOUT ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int db2k_wait_cpld_txready(struct comedi_device *dev)
{
	int i;

	for (i = 0; i < 100; i++) {
		if (readw(dev->mmio + DB2K_REG_CPLD_STATUS) &
		    DB2K_CPLD_STATUS_TXREADY) {
			return 0;
		}
		udelay(1);
	}
	return -ETIMEDOUT;
}