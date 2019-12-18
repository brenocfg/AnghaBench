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
struct hinic_api_cmd_chain {scalar_t__ cons_idx; scalar_t__ prod_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  API_CMD_TIMEOUT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  api_cmd_status_update (struct hinic_api_cmd_chain*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_for_status_poll(struct hinic_api_cmd_chain *chain)
{
	int err = -ETIMEDOUT;
	unsigned long end;

	end = jiffies + msecs_to_jiffies(API_CMD_TIMEOUT);
	do {
		api_cmd_status_update(chain);

		/* wait for CI to be updated - sign for completion */
		if (chain->cons_idx == chain->prod_idx) {
			err = 0;
			break;
		}

		msleep(20);
	} while (time_before(jiffies, end));

	return err;
}