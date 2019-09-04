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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFP_CPP_INTERFACE_TYPE_INVALID ; 
 scalar_t__ NFP_CPP_INTERFACE_TYPE_of (int /*<<< orphan*/ ) ; 
 int NFP_CPP_TARGET_MU ; 

__attribute__((used)) static int
nfp_cpp_mutex_validate(u16 interface, int *target, unsigned long long address)
{
	/* Not permitted on invalid interfaces */
	if (NFP_CPP_INTERFACE_TYPE_of(interface) ==
	    NFP_CPP_INTERFACE_TYPE_INVALID)
		return -EINVAL;

	/* Address must be 64-bit aligned */
	if (address & 7)
		return -EINVAL;

	if (*target != NFP_CPP_TARGET_MU)
		return -EINVAL;

	return 0;
}