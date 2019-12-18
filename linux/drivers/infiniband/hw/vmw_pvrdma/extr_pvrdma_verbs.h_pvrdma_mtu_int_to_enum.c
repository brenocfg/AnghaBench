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
 int PVRDMA_MTU_1024 ; 
 int PVRDMA_MTU_2048 ; 
 int PVRDMA_MTU_256 ; 
 int PVRDMA_MTU_4096 ; 
 int PVRDMA_MTU_512 ; 

__attribute__((used)) static inline enum pvrdma_mtu pvrdma_mtu_int_to_enum(int mtu)
{
	switch (mtu) {
	case 256:	return PVRDMA_MTU_256;
	case 512:	return PVRDMA_MTU_512;
	case 1024:	return PVRDMA_MTU_1024;
	case 2048:	return PVRDMA_MTU_2048;
	case 4096:
	default:	return PVRDMA_MTU_4096;
	}
}