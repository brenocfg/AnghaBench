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
typedef  int u32 ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dprintk (int,char*,int) ; 
 int /*<<< orphan*/  get_itvc_reg (struct cx231xx*,int,int*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int wait_for_mci_complete(struct cx231xx *dev)
{
	u32 gpio;
	u32 gpio_direction = 0;
	u8 count = 0;
	get_itvc_reg(dev, gpio_direction, &gpio);

	while (!(gpio&0x020000)) {
		msleep(10);

		get_itvc_reg(dev, gpio_direction, &gpio);

		if (count++ > 100) {
			dprintk(3, "ERROR: Timeout - gpio=%x\n", gpio);
			return -EIO;
		}
	}
	return 0;
}