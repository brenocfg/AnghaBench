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
struct xgpio_instance {int dummy; } ;

/* Variables and functions */
 int XGPIO_CHANNEL_OFFSET ; 
 scalar_t__ xgpio_index (struct xgpio_instance*,int) ; 

__attribute__((used)) static inline int xgpio_regoffset(struct xgpio_instance *chip, int gpio)
{
	if (xgpio_index(chip, gpio))
		return XGPIO_CHANNEL_OFFSET;

	return 0;
}