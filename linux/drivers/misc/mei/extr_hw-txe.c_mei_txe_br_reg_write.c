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
typedef  int /*<<< orphan*/  u32 ;
struct mei_txe_hw {int /*<<< orphan*/ * mem_addr; } ;

/* Variables and functions */
 size_t BRIDGE_BAR ; 
 int /*<<< orphan*/  mei_txe_reg_write (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mei_txe_br_reg_write(struct mei_txe_hw *hw,
				unsigned long offset, u32 value)
{
	mei_txe_reg_write(hw->mem_addr[BRIDGE_BAR], offset, value);
}