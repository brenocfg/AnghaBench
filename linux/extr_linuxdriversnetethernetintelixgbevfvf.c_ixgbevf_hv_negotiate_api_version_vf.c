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
struct ixgbe_hw {int dummy; } ;

/* Variables and functions */
 int IXGBE_ERR_INVALID_ARGUMENT ; 
 int ixgbe_mbox_api_10 ; 

__attribute__((used)) static int ixgbevf_hv_negotiate_api_version_vf(struct ixgbe_hw *hw, int api)
{
	/* Hyper-V only supports api version ixgbe_mbox_api_10 */
	if (api != ixgbe_mbox_api_10)
		return IXGBE_ERR_INVALID_ARGUMENT;

	return 0;
}