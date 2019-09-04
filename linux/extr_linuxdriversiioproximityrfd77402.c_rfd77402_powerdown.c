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
struct rfd77402_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFD77402_CMD_STANDBY ; 
 int /*<<< orphan*/  RFD77402_STATUS_STANDBY ; 
 int rfd77402_set_state (struct rfd77402_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfd77402_powerdown(struct rfd77402_data *data)
{
	return rfd77402_set_state(data, RFD77402_CMD_STANDBY,
				  RFD77402_STATUS_STANDBY);
}