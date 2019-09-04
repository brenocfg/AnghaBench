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
 int EIO ; 
 int /*<<< orphan*/  I8042_CMD_CTL_WCTR ; 
 int /*<<< orphan*/  I8042_CTR_AUXDIS ; 
 int /*<<< orphan*/  I8042_CTR_AUXINT ; 
 scalar_t__ i8042_command (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_ctr ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int i8042_enable_aux_port(void)
{
	i8042_ctr &= ~I8042_CTR_AUXDIS;
	i8042_ctr |= I8042_CTR_AUXINT;

	if (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR)) {
		i8042_ctr &= ~I8042_CTR_AUXINT;
		i8042_ctr |= I8042_CTR_AUXDIS;
		pr_err("Failed to enable AUX port\n");
		return -EIO;
	}

	return 0;
}