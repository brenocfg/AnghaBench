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
struct cvm_mmc_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MIO_EMM_RSP_STS (struct cvm_mmc_host*) ; 
 int MIO_EMM_RSP_STS_SWITCH_VAL ; 
 scalar_t__ MIO_EMM_SWITCH (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  check_switch_errors (struct cvm_mmc_host*) ; 
 int /*<<< orphan*/  clear_bus_id (int*) ; 
 int get_bus_id (int) ; 
 int readq (scalar_t__) ; 
 int /*<<< orphan*/  set_bus_id (int*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeq (int,scalar_t__) ; 

__attribute__((used)) static void do_switch(struct cvm_mmc_host *host, u64 emm_switch)
{
	int retries = 100;
	u64 rsp_sts;
	int bus_id;

	/*
	 * Modes setting only taken from slot 0. Work around that hardware
	 * issue by first switching to slot 0.
	 */
	bus_id = get_bus_id(emm_switch);
	clear_bus_id(&emm_switch);
	writeq(emm_switch, host->base + MIO_EMM_SWITCH(host));

	set_bus_id(&emm_switch, bus_id);
	writeq(emm_switch, host->base + MIO_EMM_SWITCH(host));

	/* wait for the switch to finish */
	do {
		rsp_sts = readq(host->base + MIO_EMM_RSP_STS(host));
		if (!(rsp_sts & MIO_EMM_RSP_STS_SWITCH_VAL))
			break;
		udelay(10);
	} while (--retries);

	check_switch_errors(host);
}