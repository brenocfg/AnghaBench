#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct cyapa_pip_cmd_states {int /*<<< orphan*/  cmd_issued; int /*<<< orphan*/  cmd_ready; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {TYPE_1__ cmd_states; } ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int cyapa_i2c_pip_write (struct cyapa*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cyapa_do_i2c_pip_cmd_irq_sync(
		struct cyapa *cyapa,
		u8 *cmd, size_t cmd_len,
		unsigned long timeout)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int error;

	/* Wait for interrupt to set ready completion */
	init_completion(&pip->cmd_ready);

	atomic_inc(&pip->cmd_issued);
	error = cyapa_i2c_pip_write(cyapa, cmd, cmd_len);
	if (error) {
		atomic_dec(&pip->cmd_issued);
		return (error < 0) ? error : -EIO;
	}

	/* Wait for interrupt to indicate command is completed. */
	timeout = wait_for_completion_timeout(&pip->cmd_ready,
				msecs_to_jiffies(timeout));
	if (timeout == 0) {
		atomic_dec(&pip->cmd_issued);
		return -ETIMEDOUT;
	}

	return 0;
}