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
struct w1_slave {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ w1_ds2405_select (struct w1_slave*,int) ; 

__attribute__((used)) static int w1_ds2405_read_pio(struct w1_slave *sl)
{
	if (w1_ds2405_select(sl, true))
		return 0; /* "active" means PIO is low */

	if (w1_ds2405_select(sl, false))
		return 1;

	return -ENODEV;
}