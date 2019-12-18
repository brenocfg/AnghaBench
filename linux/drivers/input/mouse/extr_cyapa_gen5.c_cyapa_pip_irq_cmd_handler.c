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
struct cyapa_pip_cmd_states {int is_irq_mode; int* resp_len; int /*<<< orphan*/  cmd_ready; int /*<<< orphan*/  cmd_issued; int /*<<< orphan*/  irq_cmd_buf; scalar_t__ resp_data; scalar_t__ (* resp_sort_func ) (struct cyapa*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {TYPE_1__ cmd_states; } ;

/* Variables and functions */
 int PIP_RESP_LENGTH_SIZE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cyapa_empty_pip_output_data (struct cyapa*,scalar_t__,int*,scalar_t__ (*) (struct cyapa*,int /*<<< orphan*/ ,int)) ; 
 int /*<<< orphan*/  cyapa_i2c_pip_read (struct cyapa*,int /*<<< orphan*/ ,int) ; 
 int get_unaligned_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct cyapa*,int /*<<< orphan*/ ,int) ; 

bool cyapa_pip_irq_cmd_handler(struct cyapa *cyapa)
{
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	int length;

	if (atomic_read(&pip->cmd_issued)) {
		/* Polling command response data. */
		if (pip->is_irq_mode == false)
			return false;

		/*
		 * Read out all none command response data.
		 * these output data may caused by user put finger on
		 * trackpad when host waiting the command response.
		 */
		cyapa_i2c_pip_read(cyapa, pip->irq_cmd_buf,
			PIP_RESP_LENGTH_SIZE);
		length = get_unaligned_le16(pip->irq_cmd_buf);
		length = (length <= PIP_RESP_LENGTH_SIZE) ?
				PIP_RESP_LENGTH_SIZE : length;
		if (length > PIP_RESP_LENGTH_SIZE)
			cyapa_i2c_pip_read(cyapa,
				pip->irq_cmd_buf, length);
		if (!(pip->resp_sort_func &&
			pip->resp_sort_func(cyapa,
				pip->irq_cmd_buf, length))) {
			/*
			 * Cover the Gen5 V1 firmware issue.
			 * The issue is no interrupt would be asserted from
			 * trackpad device to host for the command response
			 * ready event. Because when there was a finger touch
			 * on trackpad device, and the firmware output queue
			 * won't be empty (always with touch report data), so
			 * the interrupt signal won't be asserted again until
			 * the output queue was previous emptied.
			 * This issue would happen in the scenario that
			 * user always has his/her fingers touched on the
			 * trackpad device during system booting/rebooting.
			 */
			length = 0;
			if (pip->resp_len)
				length = *pip->resp_len;
			cyapa_empty_pip_output_data(cyapa,
					pip->resp_data,
					&length,
					pip->resp_sort_func);
			if (pip->resp_len && length != 0) {
				*pip->resp_len = length;
				atomic_dec(&pip->cmd_issued);
				complete(&pip->cmd_ready);
			}
			return false;
		}

		if (pip->resp_data && pip->resp_len) {
			*pip->resp_len = (*pip->resp_len < length) ?
				*pip->resp_len : length;
			memcpy(pip->resp_data, pip->irq_cmd_buf,
				*pip->resp_len);
		}
		atomic_dec(&pip->cmd_issued);
		complete(&pip->cmd_ready);
		return false;
	}

	return true;
}