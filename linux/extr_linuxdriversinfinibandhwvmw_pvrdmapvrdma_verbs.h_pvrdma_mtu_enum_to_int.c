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
typedef  enum pvrdma_mtu { ____Placeholder_pvrdma_mtu } pvrdma_mtu ;

/* Variables and functions */
#define  PVRDMA_MTU_1024 132 
#define  PVRDMA_MTU_2048 131 
#define  PVRDMA_MTU_256 130 
#define  PVRDMA_MTU_4096 129 
#define  PVRDMA_MTU_512 128 

__attribute__((used)) static inline int pvrdma_mtu_enum_to_int(enum pvrdma_mtu mtu)
{
	switch (mtu) {
	case PVRDMA_MTU_256:	return  256;
	case PVRDMA_MTU_512:	return  512;
	case PVRDMA_MTU_1024:	return 1024;
	case PVRDMA_MTU_2048:	return 2048;
	case PVRDMA_MTU_4096:	return 4096;
	default:		return   -1;
	}
}