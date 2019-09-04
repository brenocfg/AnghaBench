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

/* Variables and functions */
 int FAN_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clamp_val (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int FAN_TO_REG(int reg, int div)
{
	int tmp;
	tmp = FAN_FROM_REG(clamp_val(reg, 0, 65535), div);
	return tmp > 255 ? 255 : tmp;
}