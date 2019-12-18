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
typedef  int /*<<< orphan*/  u8 ;
struct stmfts_data {int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int i2c_smbus_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmfts_command(struct stmfts_data *sdata, const u8 cmd)
{
	int err;

	reinit_completion(&sdata->cmd_done);

	err = i2c_smbus_write_byte(sdata->client, cmd);
	if (err)
		return err;

	if (!wait_for_completion_timeout(&sdata->cmd_done,
					 msecs_to_jiffies(1000)))
		return -ETIMEDOUT;

	return 0;
}