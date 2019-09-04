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
struct dw_mci {TYPE_1__* dms; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_release_channel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void dw_mci_edmac_exit(struct dw_mci *host)
{
	if (host->dms) {
		if (host->dms->ch) {
			dma_release_channel(host->dms->ch);
			host->dms->ch = NULL;
		}
		kfree(host->dms);
		host->dms = NULL;
	}
}