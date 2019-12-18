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
typedef  enum wbus { ____Placeholder_wbus } wbus ;

/* Variables and functions */
#define  bus_1byte 129 
#define  bus_2byte 128 
 int /*<<< orphan*/  pr_err (char*,int) ; 

int xl_supported_prog_bus_width(enum wbus bus_bytes)
{
	switch (bus_bytes) {
	case bus_1byte:
		break;
	case bus_2byte:
		break;
	default:
		pr_err("unsupported program bus width %d\n", bus_bytes);
		return 0;
	}

	return 1;
}