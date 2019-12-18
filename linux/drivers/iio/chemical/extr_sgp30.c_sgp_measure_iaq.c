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
struct sgp_data {int /*<<< orphan*/  iaq_buffer_state; int /*<<< orphan*/  iaq_buffer; int /*<<< orphan*/  measure_iaq_cmd; scalar_t__ iaq_defval_skip_jiffies; scalar_t__ iaq_init_start_jiffies; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  IAQ_BUFFER_DEFAULT_VALS ; 
 int /*<<< orphan*/  IAQ_BUFFER_VALID ; 
 int /*<<< orphan*/  SGP_MEASUREMENT_DURATION_US ; 
 int /*<<< orphan*/  SGP_MEASUREMENT_LEN ; 
 int /*<<< orphan*/  jiffies ; 
 int sgp_read_cmd (struct sgp_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sgp_measure_iaq(struct sgp_data *data)
{
	int ret;
	/* data contains default values */
	bool default_vals = !time_after(jiffies, data->iaq_init_start_jiffies +
						 data->iaq_defval_skip_jiffies);

	ret = sgp_read_cmd(data, data->measure_iaq_cmd, &data->iaq_buffer,
			   SGP_MEASUREMENT_LEN, SGP_MEASUREMENT_DURATION_US);
	if (ret < 0)
		return ret;

	data->iaq_buffer_state = IAQ_BUFFER_DEFAULT_VALS;

	if (default_vals)
		return -EBUSY;

	data->iaq_buffer_state = IAQ_BUFFER_VALID;

	return 0;
}