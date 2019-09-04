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
typedef  int u64 ;
struct cvm_mmc_slot {int cached_switch; struct cvm_mmc_host* host; int /*<<< orphan*/  bus_id; } ;
struct cvm_mmc_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MIO_EMM_SWITCH (struct cvm_mmc_host*) ; 
 int MIO_EMM_SWITCH_ERR0 ; 
 int MIO_EMM_SWITCH_ERR1 ; 
 int MIO_EMM_SWITCH_ERR2 ; 
 int MIO_EMM_SWITCH_EXE ; 
 scalar_t__ MIO_EMM_WDOG (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  do_switch (struct cvm_mmc_host*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  set_bus_id (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void cvm_mmc_reset_bus(struct cvm_mmc_slot *slot)
{
	struct cvm_mmc_host *host = slot->host;
	u64 emm_switch, wdog;

	emm_switch = readq(slot->host->base + MIO_EMM_SWITCH(host));
	emm_switch &= ~(MIO_EMM_SWITCH_EXE | MIO_EMM_SWITCH_ERR0 |
			MIO_EMM_SWITCH_ERR1 | MIO_EMM_SWITCH_ERR2);
	set_bus_id(&emm_switch, slot->bus_id);

	wdog = readq(slot->host->base + MIO_EMM_WDOG(host));
	do_switch(slot->host, emm_switch);

	slot->cached_switch = emm_switch;

	msleep(20);

	writeq(wdog, slot->host->base + MIO_EMM_WDOG(host));
}