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
struct cyapa_pip_cmd_states {int /*<<< orphan*/  cmd_issued; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {TYPE_1__ cmd_states; } ;
typedef  scalar_t__ cb_sort ;

/* Variables and functions */
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int cyapa_empty_pip_output_data (struct cyapa*,int /*<<< orphan*/ *,int*,scalar_t__) ; 
 int cyapa_i2c_pip_write (struct cyapa*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int cyapa_do_i2c_pip_cmd_polling(
		struct cyapa *cyapa,
		u8 *cmd, size_t cmd_len,
		u8 *resp_data, int *resp_len,
		unsigned long timeout,
		cb_sort func)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int tries;
	int length;
	int error;

	atomic_inc(&pip->cmd_issued);
	error = cyapa_i2c_pip_write(cyapa, cmd, cmd_len);
	if (error) {
		atomic_dec(&pip->cmd_issued);
		return error < 0 ? error : -EIO;
	}

	length = resp_len ? *resp_len : 0;
	if (resp_data && resp_len && length != 0 && func) {
		tries = timeout / 5;
		do {
			usleep_range(3000, 5000);
			*resp_len = length;
			error = cyapa_empty_pip_output_data(cyapa,
					resp_data, resp_len, func);
			if (error || *resp_len == 0)
				continue;
			else
				break;
		} while (--tries > 0);
		if ((error || *resp_len == 0) || tries <= 0)
			error = error ? error : -ETIMEDOUT;
	}

	atomic_dec(&pip->cmd_issued);
	return error;
}