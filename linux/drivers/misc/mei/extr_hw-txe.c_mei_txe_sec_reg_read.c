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
struct mei_txe_hw {int /*<<< orphan*/  aliveness; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  mei_txe_sec_reg_read_silent (struct mei_txe_hw*,unsigned long) ; 

__attribute__((used)) static inline u32 mei_txe_sec_reg_read(struct mei_txe_hw *hw,
				unsigned long offset)
{
	WARN(!hw->aliveness, "sec read: aliveness not asserted\n");
	return mei_txe_sec_reg_read_silent(hw, offset);
}