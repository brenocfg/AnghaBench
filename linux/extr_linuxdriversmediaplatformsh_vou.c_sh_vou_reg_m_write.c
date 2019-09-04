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
struct sh_vou_device {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sh_vou_reg_m_write(struct sh_vou_device *vou_dev, unsigned int reg,
			       u32 value)
{
	__raw_writel(value, vou_dev->base + reg + 0x2000);
}