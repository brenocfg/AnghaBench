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

/* Variables and functions */
 int IB_MTU_1024 ; 
 int IB_MTU_2048 ; 
 int IB_MTU_256 ; 
 int IB_MTU_4096 ; 
 int IB_MTU_512 ; 

__attribute__((used)) static int mtu_to_enum(u32 mtu)
{
	int enum_mtu;

	switch (mtu) {
	case 4096:
		enum_mtu = IB_MTU_4096;
		break;
	case 2048:
		enum_mtu = IB_MTU_2048;
		break;
	case 1024:
		enum_mtu = IB_MTU_1024;
		break;
	case 512:
		enum_mtu = IB_MTU_512;
		break;
	case 256:
		enum_mtu = IB_MTU_256;
		break;
	default:
		enum_mtu = IB_MTU_2048;
	}
	return enum_mtu;
}