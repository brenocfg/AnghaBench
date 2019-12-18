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
struct mmci_host {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  get_datactrl_cfg; } ;

/* Variables and functions */
 TYPE_1__ mmci_variant_ops ; 
 int /*<<< orphan*/  ux500v2_get_dctrl_cfg ; 

void ux500v2_variant_init(struct mmci_host *host)
{
	host->ops = &mmci_variant_ops;
	host->ops->get_datactrl_cfg = ux500v2_get_dctrl_cfg;
}