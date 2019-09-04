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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  IOC_CONTROL ; 
 int SCL ; 
 int SDA ; 
 int force_ones ; 
 int ioc_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioc_writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ioc_setsda(void *data, int state)
{
	u_int ioc_control = ioc_readb(IOC_CONTROL) & ~(SCL | SDA);
	u_int ones = force_ones;

	if (state)
		ones |= SDA;
	else
		ones &= ~SDA;

	force_ones = ones;

 	ioc_writeb(ioc_control | ones, IOC_CONTROL);
}