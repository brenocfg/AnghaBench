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
struct mmc_host {int dummy; } ;
struct cb710_slot {int dummy; } ;

/* Variables and functions */
 int CB710_MMC_S3_CARD_DETECTED ; 
 int /*<<< orphan*/  CB710_MMC_STATUS3_PORT ; 
 struct cb710_slot* cb710_mmc_to_slot (struct mmc_host*) ; 
 int cb710_read_port_8 (struct cb710_slot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cb710_mmc_get_cd(struct mmc_host *mmc)
{
	struct cb710_slot *slot = cb710_mmc_to_slot(mmc);

	return cb710_read_port_8(slot, CB710_MMC_STATUS3_PORT)
		& CB710_MMC_S3_CARD_DETECTED;
}