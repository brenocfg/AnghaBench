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
struct rain {int /*<<< orphan*/  write_lock; int /*<<< orphan*/  cmd_reply; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_done; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rain_send (struct rain*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rain_send_and_wait(struct rain *rain,
			      const char *cmd, const char *reply)
{
	int err;

	init_completion(&rain->cmd_done);

	mutex_lock(&rain->write_lock);
	err = rain_send(rain, cmd);
	if (err)
		goto err;

	if (!wait_for_completion_timeout(&rain->cmd_done, HZ)) {
		err = -ETIMEDOUT;
		goto err;
	}
	if (reply && strncmp(rain->cmd_reply, reply, strlen(reply))) {
		dev_dbg(rain->dev,
			 "transmit of '%s': received '%s' instead of '%s'\n",
			 cmd, rain->cmd_reply, reply);
		err = -EIO;
	}
err:
	mutex_unlock(&rain->write_lock);
	return err;
}