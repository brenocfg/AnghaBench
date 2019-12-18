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
typedef  int u32 ;
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  lan9303_read_switch_reg (struct lan9303*,int,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lan9303_csr_reg_wait(struct lan9303 *chip, int regno, u32 mask)
{
	int i;

	for (i = 0; i < 25; i++) {
		u32 reg;

		lan9303_read_switch_reg(chip, regno, &reg);
		if (!(reg & mask))
			return 0;
		usleep_range(1000, 2000);
	}

	return -ETIMEDOUT;
}