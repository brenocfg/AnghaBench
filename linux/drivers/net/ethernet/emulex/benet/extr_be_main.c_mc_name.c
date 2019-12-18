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
struct be_adapter {int mc_type; } ;

/* Variables and functions */
#define  FLEX10 133 
#define  UFP 132 
#define  UMC 131 
#define  nPAR 130 
#define  vNIC1 129 
#define  vNIC2 128 

__attribute__((used)) static char *mc_name(struct be_adapter *adapter)
{
	char *str = "";	/* default */

	switch (adapter->mc_type) {
	case UMC:
		str = "UMC";
		break;
	case FLEX10:
		str = "FLEX10";
		break;
	case vNIC1:
		str = "vNIC-1";
		break;
	case nPAR:
		str = "nPAR";
		break;
	case UFP:
		str = "UFP";
		break;
	case vNIC2:
		str = "vNIC-2";
		break;
	default:
		str = "";
	}

	return str;
}