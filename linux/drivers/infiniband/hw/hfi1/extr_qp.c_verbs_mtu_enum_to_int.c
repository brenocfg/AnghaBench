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
struct ib_device {int dummy; } ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */
 scalar_t__ OPA_MTU_10240 ; 
 int OPA_MTU_8192 ; 
 int ib_mtu_enum_to_int (int) ; 
 int opa_mtu_enum_to_int (int) ; 

__attribute__((used)) static inline int verbs_mtu_enum_to_int(struct ib_device *dev, enum ib_mtu mtu)
{
	int val;

	/* Constraining 10KB packets to 8KB packets */
	if (mtu == (enum ib_mtu)OPA_MTU_10240)
		mtu = OPA_MTU_8192;
	val = opa_mtu_enum_to_int((int)mtu);
	if (val > 0)
		return val;
	return ib_mtu_enum_to_int(mtu);
}