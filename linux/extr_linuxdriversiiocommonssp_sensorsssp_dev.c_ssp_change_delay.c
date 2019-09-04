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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  to_send ;
struct ssp_instruction {int /*<<< orphan*/  c; void* b; void* a; } ;
struct ssp_data {int /*<<< orphan*/ * delay_buf; TYPE_1__* spi; int /*<<< orphan*/ * batch_opt_buf; int /*<<< orphan*/ * batch_latency_buf; } ;
typedef  enum ssp_sensor_type { ____Placeholder_ssp_sensor_type } ssp_sensor_type ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSP_MSG2SSP_INST_CHANGE_DELAY ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int ssp_send_instruction (struct ssp_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

int ssp_change_delay(struct ssp_data *data, enum ssp_sensor_type type,
		     u32 delay)
{
	int ret;
	struct ssp_instruction to_send;

	to_send.a = cpu_to_le32(delay);
	to_send.b = cpu_to_le32(data->batch_latency_buf[type]);
	to_send.c = data->batch_opt_buf[type];

	ret = ssp_send_instruction(data, SSP_MSG2SSP_INST_CHANGE_DELAY, type,
				   (u8 *)&to_send, sizeof(to_send));
	if (ret < 0) {
		dev_err(&data->spi->dev, "Changing sensor delay failed\n");
		return ret;
	}

	data->delay_buf[type] = delay;

	return 0;
}