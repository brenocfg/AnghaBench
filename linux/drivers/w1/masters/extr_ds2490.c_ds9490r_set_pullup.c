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
typedef  int u8 ;
struct ds_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ds_set_pullup (struct ds_device*,int) ; 

__attribute__((used)) static u8 ds9490r_set_pullup(void *data, int delay)
{
	struct ds_device *dev = data;

	if (ds_set_pullup(dev, delay))
		return 1;

	return 0;
}