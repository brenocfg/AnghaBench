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

/* Variables and functions */
#define  OPA_MTU_10240 129 
#define  OPA_MTU_8192 128 

__attribute__((used)) static inline int opa_mtu_enum_to_int(int mtu)
{
	switch (mtu) {
	case OPA_MTU_8192:  return 8192;
	case OPA_MTU_10240: return 10240;
	default:            return -1;
	}
}