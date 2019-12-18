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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_card {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EILSEQ ; 
 int mmc_send_status (struct mmc_card*,int /*<<< orphan*/ *) ; 
 int mmc_switch_status_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __mmc_switch_status(struct mmc_card *card, bool crc_err_fatal)
{
	u32 status;
	int err;

	err = mmc_send_status(card, &status);
	if (!crc_err_fatal && err == -EILSEQ)
		return 0;
	if (err)
		return err;

	return mmc_switch_status_error(card->host, status);
}