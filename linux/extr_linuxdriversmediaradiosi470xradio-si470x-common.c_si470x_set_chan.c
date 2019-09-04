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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct si470x_device {int (* get_register ) (struct si470x_device*,size_t) ;int* registers; int (* set_register ) (struct si470x_device*,size_t) ;TYPE_1__ videodev; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 size_t CHANNEL ; 
 int CHANNEL_CHAN ; 
 unsigned short CHANNEL_TUNE ; 
 size_t POWERCFG ; 
 int POWERCFG_DMUTE ; 
 int POWERCFG_ENABLE ; 
 size_t STATUSRSSI ; 
 int STATUSRSSI_STC ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct si470x_device*,size_t) ; 
 int stub2 (struct si470x_device*,size_t) ; 
 int stub3 (struct si470x_device*,size_t) ; 
 int /*<<< orphan*/  tune_timeout ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si470x_set_chan(struct si470x_device *radio, unsigned short chan)
{
	int retval;
	unsigned long time_left;
	bool timed_out = false;

	retval = radio->get_register(radio, POWERCFG);
	if (retval)
		return retval;

	if ((radio->registers[POWERCFG] & (POWERCFG_ENABLE|POWERCFG_DMUTE))
		!= (POWERCFG_ENABLE|POWERCFG_DMUTE)) {
		return 0;
	}

	/* start tuning */
	radio->registers[CHANNEL] &= ~CHANNEL_CHAN;
	radio->registers[CHANNEL] |= CHANNEL_TUNE | chan;
	retval = radio->set_register(radio, CHANNEL);
	if (retval < 0)
		goto done;

	/* wait till tune operation has completed */
	reinit_completion(&radio->completion);
	time_left = wait_for_completion_timeout(&radio->completion,
						msecs_to_jiffies(tune_timeout));
	if (time_left == 0)
		timed_out = true;

	if ((radio->registers[STATUSRSSI] & STATUSRSSI_STC) == 0)
		dev_warn(&radio->videodev.dev, "tune does not complete\n");
	if (timed_out)
		dev_warn(&radio->videodev.dev,
			"tune timed out after %u ms\n", tune_timeout);

	/* stop tuning */
	radio->registers[CHANNEL] &= ~CHANNEL_TUNE;
	retval = radio->set_register(radio, CHANNEL);

done:
	return retval;
}