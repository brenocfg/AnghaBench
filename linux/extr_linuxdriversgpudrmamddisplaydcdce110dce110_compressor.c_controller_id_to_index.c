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
typedef  enum controller_id { ____Placeholder_controller_id } controller_id ;

/* Variables and functions */
#define  CONTROLLER_ID_D0 131 
#define  CONTROLLER_ID_D1 130 
#define  CONTROLLER_ID_D2 129 
#define  CONTROLLER_ID_D3 128 

unsigned int controller_id_to_index(enum controller_id controller_id)
{
	unsigned int index = 0;

	switch (controller_id) {
	case CONTROLLER_ID_D0:
		index = 0;
		break;
	case CONTROLLER_ID_D1:
		index = 1;
		break;
	case CONTROLLER_ID_D2:
		index = 2;
		break;
	case CONTROLLER_ID_D3:
		index = 3;
		break;
	default:
		break;
	}
	return index;
}