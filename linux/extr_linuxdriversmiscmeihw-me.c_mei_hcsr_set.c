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
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_CSR_IS_MASK ; 
 int /*<<< orphan*/  mei_hcsr_write (struct mei_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mei_hcsr_set(struct mei_device *dev, u32 reg)
{
	reg &= ~H_CSR_IS_MASK;
	mei_hcsr_write(dev, reg);
}