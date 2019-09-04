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
typedef  int uint32_t ;

/* Variables and functions */
#define  ATOM_DEVICE_CRT1_SUPPORT 134 
 int ATOM_DEVICE_CRT2_SUPPORT ; 
#define  ATOM_DEVICE_DFP1_SUPPORT 133 
#define  ATOM_DEVICE_DFP2_SUPPORT 132 
#define  ATOM_DEVICE_DFP3_SUPPORT 131 
#define  ATOM_DEVICE_DFP4_SUPPORT 130 
#define  ATOM_DEVICE_DFP5_SUPPORT 129 
 int ATOM_DEVICE_DFP6_SUPPORT ; 
#define  ATOM_DEVICE_LCD1_SUPPORT 128 
 int ATOM_DEVICE_LCD2_SUPPORT ; 

__attribute__((used)) static uint32_t enum_next_dev_id(uint32_t dev_id)
{
	/* Get next device ID in the group. */
	switch (dev_id) {
	case ATOM_DEVICE_CRT1_SUPPORT:
		return ATOM_DEVICE_CRT2_SUPPORT;
	case ATOM_DEVICE_LCD1_SUPPORT:
		return ATOM_DEVICE_LCD2_SUPPORT;
	case ATOM_DEVICE_DFP1_SUPPORT:
		return ATOM_DEVICE_DFP2_SUPPORT;
	case ATOM_DEVICE_DFP2_SUPPORT:
		return ATOM_DEVICE_DFP3_SUPPORT;
	case ATOM_DEVICE_DFP3_SUPPORT:
		return ATOM_DEVICE_DFP4_SUPPORT;
	case ATOM_DEVICE_DFP4_SUPPORT:
		return ATOM_DEVICE_DFP5_SUPPORT;
	case ATOM_DEVICE_DFP5_SUPPORT:
		return ATOM_DEVICE_DFP6_SUPPORT;
	}

	/* Done enumerating through devices. */
	return 0;
}