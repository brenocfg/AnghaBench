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
struct e1000_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_read_flash_data32_ich8lan (struct e1000_hw*,int,int*) ; 

__attribute__((used)) static s32 e1000_read_flash_dword_ich8lan(struct e1000_hw *hw, u32 offset,
					  u32 *data)
{
	/* Must convert word offset into bytes. */
	offset <<= 1;
	return e1000_read_flash_data32_ich8lan(hw, offset, data);
}