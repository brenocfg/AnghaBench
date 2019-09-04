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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct malidp_hw_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MALIDP_REG_MASKIRQ ; 
 scalar_t__ malidp_get_block_base (struct malidp_hw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_hw_setbits (struct malidp_hw_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void malidp_hw_enable_irq(struct malidp_hw_device *hwdev,
					u8 block, u32 irq)
{
	u32 base = malidp_get_block_base(hwdev, block);

	malidp_hw_setbits(hwdev, irq, base + MALIDP_REG_MASKIRQ);
}