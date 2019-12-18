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
struct sgp_data {int measure_interval_jiffies; int product_id; int iaq_defval_skip_jiffies; void* measure_gas_signals_cmd; void* measure_iaq_cmd; int /*<<< orphan*/  iaq_buffer_state; scalar_t__ iaq_init_start_jiffies; int /*<<< orphan*/  iaq_init_cmd; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IAQ_BUFFER_EMPTY ; 
#define  SGP30 129 
 void* SGP30_CMD_MEASURE_SIGNAL ; 
 int SGP30_MEASURE_INTERVAL_HZ ; 
#define  SGPC3 128 
 void* SGPC3_CMD_MEASURE_RAW ; 
 int SGPC3_MEASURE_INTERVAL_HZ ; 
 int /*<<< orphan*/  SGP_CMD_IAQ_INIT ; 
 void* SGP_CMD_IAQ_MEASURE ; 
 int SGP_VERS_PRODUCT (struct sgp_data*) ; 

__attribute__((used)) static void sgp_init(struct sgp_data *data)
{
	data->iaq_init_cmd = SGP_CMD_IAQ_INIT;
	data->iaq_init_start_jiffies = 0;
	data->iaq_buffer_state = IAQ_BUFFER_EMPTY;
	switch (SGP_VERS_PRODUCT(data)) {
	case SGP30:
		data->measure_interval_jiffies = SGP30_MEASURE_INTERVAL_HZ * HZ;
		data->measure_iaq_cmd = SGP_CMD_IAQ_MEASURE;
		data->measure_gas_signals_cmd = SGP30_CMD_MEASURE_SIGNAL;
		data->product_id = SGP30;
		data->iaq_defval_skip_jiffies = 15 * HZ;
		break;
	case SGPC3:
		data->measure_interval_jiffies = SGPC3_MEASURE_INTERVAL_HZ * HZ;
		data->measure_iaq_cmd = SGPC3_CMD_MEASURE_RAW;
		data->measure_gas_signals_cmd = SGPC3_CMD_MEASURE_RAW;
		data->product_id = SGPC3;
		data->iaq_defval_skip_jiffies =
			43 * data->measure_interval_jiffies;
		break;
	};
}