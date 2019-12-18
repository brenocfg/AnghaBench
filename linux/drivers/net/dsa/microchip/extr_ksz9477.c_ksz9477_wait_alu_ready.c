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
struct ksz_device {int /*<<< orphan*/ * regmap; } ;

/* Variables and functions */
 unsigned int ALU_START ; 
 int /*<<< orphan*/  REG_SW_ALU_CTRL__4 ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int,int) ; 

__attribute__((used)) static int ksz9477_wait_alu_ready(struct ksz_device *dev)
{
	unsigned int val;

	return regmap_read_poll_timeout(dev->regmap[2], REG_SW_ALU_CTRL__4,
					val, !(val & ALU_START), 10, 1000);
}