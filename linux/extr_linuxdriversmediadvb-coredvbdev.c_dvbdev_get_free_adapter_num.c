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

/* Variables and functions */
 int DVB_MAX_ADAPTERS ; 
 int ENFILE ; 
 scalar_t__ dvbdev_check_free_adapter_num (int) ; 

__attribute__((used)) static int dvbdev_get_free_adapter_num (void)
{
	int num = 0;

	while (num < DVB_MAX_ADAPTERS) {
		if (dvbdev_check_free_adapter_num(num))
			return num;
		num++;
	}

	return -ENFILE;
}