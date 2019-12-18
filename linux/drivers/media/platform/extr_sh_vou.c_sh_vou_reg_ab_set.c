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
struct sh_vou_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sh_vou_reg_a_set (struct sh_vou_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_vou_reg_b_set (struct sh_vou_device*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sh_vou_reg_ab_set(struct sh_vou_device *vou_dev, unsigned int reg,
			      u32 value, u32 mask)
{
	sh_vou_reg_a_set(vou_dev, reg, value, mask);
	sh_vou_reg_b_set(vou_dev, reg, value, mask);
}