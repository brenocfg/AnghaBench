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
struct adt7462_data {int* pin_cfg; } ;

/* Variables and functions */
 int ADT7462_DIODE1_INPUT ; 
 int ADT7462_DIODE3_INPUT ; 

__attribute__((used)) static const char *temp_label(struct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		return "local";
	case 1:
		if (data->pin_cfg[0] & ADT7462_DIODE1_INPUT)
			return "remote1";
		break;
	case 2:
		return "remote2";
	case 3:
		if (data->pin_cfg[0] & ADT7462_DIODE3_INPUT)
			return "remote3";
		break;
	}
	return "N/A";
}