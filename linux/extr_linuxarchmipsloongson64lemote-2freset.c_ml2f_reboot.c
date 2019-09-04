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
 int /*<<< orphan*/  BIT_RESET_ON ; 
 int /*<<< orphan*/  REG_RESET ; 
 int /*<<< orphan*/  ec_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_cpu () ; 

__attribute__((used)) static void ml2f_reboot(void)
{
	reset_cpu();

	/* sending an reset signal to EC(embedded controller) */
	ec_write(REG_RESET, BIT_RESET_ON);
}