#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* spidev; } ;
struct st95hf_context {TYPE_2__ spicontext; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 unsigned char ST95HF_COMMAND_RESET ; 
 int /*<<< orphan*/  ST95HF_RESET_CMD_LEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  st95hf_send_st95enable_negativepulse (struct st95hf_context*) ; 
 int st95hf_spi_send (TYPE_2__*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int st95hf_send_spi_reset_sequence(struct st95hf_context *st95context)
{
	int result = 0;
	unsigned char reset_cmd = ST95HF_COMMAND_RESET;

	result = st95hf_spi_send(&st95context->spicontext,
				 &reset_cmd,
				 ST95HF_RESET_CMD_LEN,
				 ASYNC);
	if (result) {
		dev_err(&st95context->spicontext.spidev->dev,
			"spi reset sequence cmd error = %d", result);
		return result;
	}

	/* wait for 3 milisecond to complete the controller reset process */
	usleep_range(3000, 4000);

	/* send negative pulse to make st95hf active */
	st95hf_send_st95enable_negativepulse(st95context);

	/* wait for 10 milisecond : HFO setup time */
	usleep_range(10000, 20000);

	return result;
}