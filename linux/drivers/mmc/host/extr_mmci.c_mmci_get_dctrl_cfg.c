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
struct mmci_host {int dummy; } ;

/* Variables and functions */
 int MCI_DPSM_ENABLE ; 
 int mmci_dctrl_blksz (struct mmci_host*) ; 

__attribute__((used)) static u32 mmci_get_dctrl_cfg(struct mmci_host *host)
{
	return MCI_DPSM_ENABLE | mmci_dctrl_blksz(host);
}