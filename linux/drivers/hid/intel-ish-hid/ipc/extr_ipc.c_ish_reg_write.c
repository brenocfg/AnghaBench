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
typedef  int /*<<< orphan*/  uint32_t ;
struct ishtp_device {int dummy; } ;
struct ish_hw {scalar_t__ mem_addr; } ;

/* Variables and functions */
 struct ish_hw* to_ish_hw (struct ishtp_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void ish_reg_write(struct ishtp_device *dev,
				 unsigned long offset,
				 uint32_t value)
{
	struct ish_hw *hw = to_ish_hw(dev);

	writel(value, hw->mem_addr + offset);
}