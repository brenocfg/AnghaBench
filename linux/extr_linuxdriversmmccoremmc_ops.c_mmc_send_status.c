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
struct mmc_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CMD_RETRIES ; 
 int __mmc_send_status (struct mmc_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mmc_send_status(struct mmc_card *card, u32 *status)
{
	return __mmc_send_status(card, status, MMC_CMD_RETRIES);
}