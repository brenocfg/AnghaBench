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
 size_t SEC_BAR ; 
 int /*<<< orphan*/  mei_txe_reg_read (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline u32 mei_txe_sec_reg_read_silent(struct mei_txe_hw *hw,
				unsigned long offset)
{
	return mei_txe_reg_read(hw->mem_addr[SEC_BAR], offset);
}