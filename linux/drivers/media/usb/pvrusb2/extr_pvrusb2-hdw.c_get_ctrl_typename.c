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
typedef  enum pvr2_ctl_type { ____Placeholder_pvr2_ctl_type } pvr2_ctl_type ;

/* Variables and functions */
#define  pvr2_ctl_bitmask 131 
#define  pvr2_ctl_bool 130 
#define  pvr2_ctl_enum 129 
#define  pvr2_ctl_int 128 

__attribute__((used)) static const char *get_ctrl_typename(enum pvr2_ctl_type tp)
{
	switch (tp) {
	case pvr2_ctl_int: return "integer";
	case pvr2_ctl_enum: return "enum";
	case pvr2_ctl_bool: return "boolean";
	case pvr2_ctl_bitmask: return "bitmask";
	}
	return "";
}