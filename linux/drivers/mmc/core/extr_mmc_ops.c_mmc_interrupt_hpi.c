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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  out_of_int_time; int /*<<< orphan*/  hpi_en; } ;
struct mmc_card {TYPE_1__ ext_csd; int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int const R1_CURRENT_STATE (int /*<<< orphan*/ ) ; 
#define  R1_STATE_IDLE 132 
#define  R1_STATE_PRG 131 
#define  R1_STATE_READY 130 
#define  R1_STATE_STBY 129 
#define  R1_STATE_TRAN 128 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int mmc_send_hpi_cmd (struct mmc_card*,int /*<<< orphan*/ *) ; 
 int mmc_send_status (struct mmc_card*,int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

int mmc_interrupt_hpi(struct mmc_card *card)
{
	int err;
	u32 status;
	unsigned long prg_wait;

	if (!card->ext_csd.hpi_en) {
		pr_info("%s: HPI enable bit unset\n", mmc_hostname(card->host));
		return 1;
	}

	err = mmc_send_status(card, &status);
	if (err) {
		pr_err("%s: Get card status fail\n", mmc_hostname(card->host));
		goto out;
	}

	switch (R1_CURRENT_STATE(status)) {
	case R1_STATE_IDLE:
	case R1_STATE_READY:
	case R1_STATE_STBY:
	case R1_STATE_TRAN:
		/*
		 * In idle and transfer states, HPI is not needed and the caller
		 * can issue the next intended command immediately
		 */
		goto out;
	case R1_STATE_PRG:
		break;
	default:
		/* In all other states, it's illegal to issue HPI */
		pr_debug("%s: HPI cannot be sent. Card state=%d\n",
			mmc_hostname(card->host), R1_CURRENT_STATE(status));
		err = -EINVAL;
		goto out;
	}

	err = mmc_send_hpi_cmd(card, &status);
	if (err)
		goto out;

	prg_wait = jiffies + msecs_to_jiffies(card->ext_csd.out_of_int_time);
	do {
		err = mmc_send_status(card, &status);

		if (!err && R1_CURRENT_STATE(status) == R1_STATE_TRAN)
			break;
		if (time_after(jiffies, prg_wait))
			err = -ETIMEDOUT;
	} while (!err);

out:
	return err;
}