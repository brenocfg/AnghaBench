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
 int /*<<< orphan*/  mei_txe_sec_reg_write_silent (struct mei_txe_hw*,unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mei_txe_sec_reg_write(struct mei_txe_hw *hw,
				unsigned long offset, u32 value)
{
	WARN(!hw->aliveness, "sec write: aliveness not asserted\n");
	mei_txe_sec_reg_write_silent(hw, offset, value);
}