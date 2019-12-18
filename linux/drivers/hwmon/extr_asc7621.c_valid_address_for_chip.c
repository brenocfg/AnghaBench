#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* addresses; } ;

/* Variables and functions */
 int I2C_CLIENT_END ; 
 TYPE_1__* asc7621_chips ; 

__attribute__((used)) static inline int valid_address_for_chip(int chip_type, int address)
{
	int i;

	for (i = 0; asc7621_chips[chip_type].addresses[i] != I2C_CLIENT_END;
	     i++) {
		if (asc7621_chips[chip_type].addresses[i] == address)
			return 1;
	}
	return 0;
}