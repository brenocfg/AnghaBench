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
struct input_dev {scalar_t__ users; } ;
struct cyapa_pip_report_data {int dummy; } ;
struct cyapa_pip_cmd_states {scalar_t__ empty_buf; } ;
struct TYPE_2__ {struct cyapa_pip_cmd_states pip; } ;
struct cyapa {scalar_t__ operational; TYPE_1__ cmd_states; struct input_dev* input; } ;
typedef  enum cyapa_pm_stage { ____Placeholder_cyapa_pm_stage } cyapa_pm_stage ;
typedef  scalar_t__ (* cb_sort ) (struct cyapa*,scalar_t__,int) ;

/* Variables and functions */
 int CYAPA_PM_RUNTIME_RESUME ; 
 int CYAPA_PM_RUNTIME_SUSPEND ; 
 int CYAPA_REG_MAP_SIZE ; 
 int EINVAL ; 
 int PIP_RESP_LENGTH_SIZE ; 
 int cyapa_get_pip_pm_state (struct cyapa*) ; 
 int cyapa_i2c_pip_read (struct cyapa*,scalar_t__,int) ; 
 int /*<<< orphan*/  cyapa_pip_event_process (struct cyapa*,struct cyapa_pip_report_data*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int min (int,int) ; 

int cyapa_empty_pip_output_data(struct cyapa *cyapa,
		u8 *buf, int *len, cb_sort func)
{
	struct input_dev *input = cyapa->input;
	struct cyapa_pip_cmd_states *pip = &cyapa->cmd_states.pip;
	enum cyapa_pm_stage pm_stage = cyapa_get_pip_pm_state(cyapa);
	int length;
	int report_count;
	int empty_count;
	int buf_len;
	int error;

	buf_len = 0;
	if (len) {
		buf_len = (*len < CYAPA_REG_MAP_SIZE) ?
				*len : CYAPA_REG_MAP_SIZE;
		*len = 0;
	}

	report_count = 8;  /* max 7 pending data before command response data */
	empty_count = 0;
	do {
		/*
		 * Depending on testing in cyapa driver, there are max 5 "02 00"
		 * packets between two valid buffered data report in firmware.
		 * So in order to dump all buffered data out and
		 * make interrupt line release for reassert again,
		 * we must set the empty_count check value bigger than 5 to
		 * make it work. Otherwise, in some situation,
		 * the interrupt line may unable to reactive again,
		 * which will cause trackpad device unable to
		 * report data any more.
		 * for example, it may happen in EFT and ESD testing.
		 */
		if (empty_count > 5)
			return 0;

		error = cyapa_i2c_pip_read(cyapa, pip->empty_buf,
				PIP_RESP_LENGTH_SIZE);
		if (error < 0)
			return error;

		length = get_unaligned_le16(pip->empty_buf);
		if (length == PIP_RESP_LENGTH_SIZE) {
			empty_count++;
			continue;
		} else if (length > CYAPA_REG_MAP_SIZE) {
			/* Should not happen */
			return -EINVAL;
		} else if (length == 0) {
			/* Application or bootloader launch data polled out. */
			length = PIP_RESP_LENGTH_SIZE;
			if (buf && buf_len && func &&
				func(cyapa, pip->empty_buf, length)) {
				length = min(buf_len, length);
				memcpy(buf, pip->empty_buf, length);
				*len = length;
				/* Response found, success. */
				return 0;
			}
			continue;
		}

		error = cyapa_i2c_pip_read(cyapa, pip->empty_buf, length);
		if (error < 0)
			return error;

		report_count--;
		empty_count = 0;
		length = get_unaligned_le16(pip->empty_buf);
		if (length <= PIP_RESP_LENGTH_SIZE) {
			empty_count++;
		} else if (buf && buf_len && func &&
			func(cyapa, pip->empty_buf, length)) {
			length = min(buf_len, length);
			memcpy(buf, pip->empty_buf, length);
			*len = length;
			/* Response found, success. */
			return 0;
		} else if (cyapa->operational && input && input->users &&
			   (pm_stage == CYAPA_PM_RUNTIME_RESUME ||
			    pm_stage == CYAPA_PM_RUNTIME_SUSPEND)) {
			/* Parse the data and report it if it's valid. */
			cyapa_pip_event_process(cyapa,
			       (struct cyapa_pip_report_data *)pip->empty_buf);
		}

		error = -EINVAL;
	} while (report_count);

	return error;
}