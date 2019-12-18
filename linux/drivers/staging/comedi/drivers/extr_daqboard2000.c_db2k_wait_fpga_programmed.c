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
typedef  int u32 ;
struct db2k_private {scalar_t__ plx; } ;
struct comedi_device {struct db2k_private* private; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int PLX_CNTRL_USERI ; 
 scalar_t__ PLX_REG_CNTRL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int db2k_wait_fpga_programmed(struct comedi_device *dev)
{
	struct db2k_private *devpriv = dev->private;
	int i;

	/* Time out after 200 tries -> 20ms */
	for (i = 0; i < 200; i++) {
		u32 cntrl = readl(devpriv->plx + PLX_REG_CNTRL);
		/* General Purpose Input (USERI) set on FPGA "DONE". */
		if (cntrl & PLX_CNTRL_USERI)
			return 0;

		usleep_range(100, 1000);
	}
	return -ETIMEDOUT;
}