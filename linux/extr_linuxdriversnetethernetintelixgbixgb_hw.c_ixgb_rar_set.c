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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct ixgb_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int IXGB_RAH_AV ; 
 int /*<<< orphan*/  IXGB_WRITE_REG_ARRAY (struct ixgb_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  RA ; 

void
ixgb_rar_set(struct ixgb_hw *hw,
		  u8 *addr,
		  u32 index)
{
	u32 rar_low, rar_high;

	ENTER();

	/* HW expects these in little endian so we reverse the byte order
	 * from network order (big endian) to little endian
	 */
	rar_low = ((u32) addr[0] |
		   ((u32)addr[1] << 8) |
		   ((u32)addr[2] << 16) |
		   ((u32)addr[3] << 24));

	rar_high = ((u32) addr[4] |
			((u32)addr[5] << 8) |
			IXGB_RAH_AV);

	IXGB_WRITE_REG_ARRAY(hw, RA, (index << 1), rar_low);
	IXGB_WRITE_REG_ARRAY(hw, RA, ((index << 1) + 1), rar_high);
}