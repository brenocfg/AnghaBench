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
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int GMR_FS_ANY_ERR ; 
 int GMR_FS_RX_OK ; 
 int XMR_FS_2L_VLAN ; 
 int XMR_FS_ERR ; 
 scalar_t__ is_genesis (struct skge_hw const*) ; 

__attribute__((used)) static inline int bad_phy_status(const struct skge_hw *hw, u32 status)
{
	if (is_genesis(hw))
		return (status & (XMR_FS_ERR | XMR_FS_2L_VLAN)) != 0;
	else
		return (status & GMR_FS_ANY_ERR) ||
			(status & GMR_FS_RX_OK) == 0;
}