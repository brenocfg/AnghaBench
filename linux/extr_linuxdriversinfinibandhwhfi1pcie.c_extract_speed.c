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
typedef  int u32 ;
typedef  int u16 ;

/* Variables and functions */
 int PCI_EXP_LNKSTA_CLS ; 
#define  PCI_EXP_LNKSTA_CLS_2_5GB 130 
#define  PCI_EXP_LNKSTA_CLS_5_0GB 129 
#define  PCI_EXP_LNKSTA_CLS_8_0GB 128 

__attribute__((used)) static u32 extract_speed(u16 linkstat)
{
	u32 speed;

	switch (linkstat & PCI_EXP_LNKSTA_CLS) {
	default: /* not defined, assume Gen1 */
	case PCI_EXP_LNKSTA_CLS_2_5GB:
		speed = 2500; /* Gen 1, 2.5GHz */
		break;
	case PCI_EXP_LNKSTA_CLS_5_0GB:
		speed = 5000; /* Gen 2, 5GHz */
		break;
	case PCI_EXP_LNKSTA_CLS_8_0GB:
		speed = 8000; /* Gen 3, 8GHz */
		break;
	}
	return speed;
}