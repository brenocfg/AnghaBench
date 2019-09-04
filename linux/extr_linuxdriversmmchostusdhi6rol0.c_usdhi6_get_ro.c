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
typedef  int u32 ;
struct usdhi6_host {int dummy; } ;
struct mmc_host {int caps2; } ;

/* Variables and functions */
 int MMC_CAP2_RO_ACTIVE_HIGH ; 
 int /*<<< orphan*/  USDHI6_SD_INFO1 ; 
 int USDHI6_SD_INFO1_WP ; 
 struct usdhi6_host* mmc_priv (struct mmc_host*) ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usdhi6_get_ro(struct mmc_host *mmc)
{
	struct usdhi6_host *host = mmc_priv(mmc);
	/* No locking as above */
	u32 status = usdhi6_read(host, USDHI6_SD_INFO1) & USDHI6_SD_INFO1_WP;

/*
 *	level	status.WP	RO_ACTIVE_HIGH	card read-only
 *	1	0		0		0
 *	1	0		1		1
 *	0	1		0		1
 *	0	1		1		0
 */
	return !status ^ !(mmc->caps2 & MMC_CAP2_RO_ACTIVE_HIGH);
}