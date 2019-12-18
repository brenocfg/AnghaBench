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
typedef  int u16 ;
struct via_crdr_mmc_host {TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 int VIA_CRDR_SDSTS_DT ; 
 int VIA_CRDR_SDSTS_RC ; 
 int VIA_CRDR_SDSTS_WC ; 
 int /*<<< orphan*/  via_sdc_finish_data (struct via_crdr_mmc_host*) ; 

__attribute__((used)) static void via_sdc_data_isr(struct via_crdr_mmc_host *host, u16 intmask)
{
	BUG_ON(intmask == 0);

	if (intmask & VIA_CRDR_SDSTS_DT)
		host->data->error = -ETIMEDOUT;
	else if (intmask & (VIA_CRDR_SDSTS_RC | VIA_CRDR_SDSTS_WC))
		host->data->error = -EILSEQ;

	via_sdc_finish_data(host);
}