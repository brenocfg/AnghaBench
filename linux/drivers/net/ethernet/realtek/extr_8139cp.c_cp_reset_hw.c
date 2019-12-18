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
struct cp_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd ; 
 int CmdReset ; 
 int cpr8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static void cp_reset_hw (struct cp_private *cp)
{
	unsigned work = 1000;

	cpw8(Cmd, CmdReset);

	while (work--) {
		if (!(cpr8(Cmd) & CmdReset))
			return;

		schedule_timeout_uninterruptible(10);
	}

	netdev_err(cp->dev, "hardware reset timeout\n");
}