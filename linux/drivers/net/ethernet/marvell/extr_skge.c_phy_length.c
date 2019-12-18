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
typedef  int u16 ;
struct skge_hw {int dummy; } ;

/* Variables and functions */
 int GMR_FS_LEN_SHIFT ; 
 int XMR_FS_LEN_SHIFT ; 
 scalar_t__ is_genesis (struct skge_hw const*) ; 

__attribute__((used)) static inline u16 phy_length(const struct skge_hw *hw, u32 status)
{
	if (is_genesis(hw))
		return status >> XMR_FS_LEN_SHIFT;
	else
		return status >> GMR_FS_LEN_SHIFT;
}