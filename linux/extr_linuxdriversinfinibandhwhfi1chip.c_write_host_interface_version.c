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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERAL_CONFIG ; 
 int HOST_INTERFACE_VERSION_MASK ; 
 int HOST_INTERFACE_VERSION_SHIFT ; 
 int /*<<< orphan*/  RESERVED_REGISTERS ; 
 int load_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_8051_config (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int write_host_interface_version(struct hfi1_devdata *dd, u8 version)
{
	u32 frame;
	u32 mask;

	mask = (HOST_INTERFACE_VERSION_MASK << HOST_INTERFACE_VERSION_SHIFT);
	read_8051_config(dd, RESERVED_REGISTERS, GENERAL_CONFIG, &frame);
	/* Clear, then set field */
	frame &= ~mask;
	frame |= ((u32)version << HOST_INTERFACE_VERSION_SHIFT);
	return load_8051_config(dd, RESERVED_REGISTERS, GENERAL_CONFIG,
				frame);
}