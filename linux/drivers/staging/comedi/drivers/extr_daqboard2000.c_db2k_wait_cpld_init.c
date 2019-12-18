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
struct comedi_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int DB2K_CPLD_STATUS_INIT ; 
 scalar_t__ DB2K_REG_CPLD_STATUS ; 
 int ETIMEDOUT ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int db2k_wait_cpld_init(struct comedi_device *dev)
{
	int result = -ETIMEDOUT;
	int i;
	u16 cpld;

	/* timeout after 50 tries -> 5ms */
	for (i = 0; i < 50; i++) {
		cpld = readw(dev->mmio + DB2K_REG_CPLD_STATUS);
		if (cpld & DB2K_CPLD_STATUS_INIT) {
			result = 0;
			break;
		}
		usleep_range(100, 1000);
	}
	udelay(5);
	return result;
}