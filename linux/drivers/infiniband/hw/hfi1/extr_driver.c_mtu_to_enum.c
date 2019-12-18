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
 int OPA_MTU_0 ; 
 int OPA_MTU_1024 ; 
 int OPA_MTU_10240 ; 
 int OPA_MTU_2048 ; 
 int OPA_MTU_256 ; 
 int OPA_MTU_4096 ; 
 int OPA_MTU_512 ; 
 int OPA_MTU_8192 ; 

int mtu_to_enum(u32 mtu, int default_if_bad)
{
	switch (mtu) {
	case     0: return OPA_MTU_0;
	case   256: return OPA_MTU_256;
	case   512: return OPA_MTU_512;
	case  1024: return OPA_MTU_1024;
	case  2048: return OPA_MTU_2048;
	case  4096: return OPA_MTU_4096;
	case  8192: return OPA_MTU_8192;
	case 10240: return OPA_MTU_10240;
	}
	return default_if_bad;
}