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
typedef  int u16 ;

/* Variables and functions */
#define  OPA_MTU_0 135 
#define  OPA_MTU_1024 134 
#define  OPA_MTU_10240 133 
#define  OPA_MTU_2048 132 
#define  OPA_MTU_256 131 
#define  OPA_MTU_4096 130 
#define  OPA_MTU_512 129 
#define  OPA_MTU_8192 128 

u16 enum_to_mtu(int mtu)
{
	switch (mtu) {
	case OPA_MTU_0:     return 0;
	case OPA_MTU_256:   return 256;
	case OPA_MTU_512:   return 512;
	case OPA_MTU_1024:  return 1024;
	case OPA_MTU_2048:  return 2048;
	case OPA_MTU_4096:  return 4096;
	case OPA_MTU_8192:  return 8192;
	case OPA_MTU_10240: return 10240;
	default: return 0xffff;
	}
}