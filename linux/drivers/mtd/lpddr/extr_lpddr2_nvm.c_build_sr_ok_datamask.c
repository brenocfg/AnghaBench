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
 int SR_OK_DATAMASK ; 

__attribute__((used)) static inline u_int build_sr_ok_datamask(u_int bus_width)
{
	u_int val = SR_OK_DATAMASK;

	if (bus_width == 0x0004)		/* x32 device */
		val = (val << 16)+val;

	return val;
}