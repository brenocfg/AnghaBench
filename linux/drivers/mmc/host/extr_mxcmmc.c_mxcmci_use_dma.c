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
struct mxcmci_host {int do_dma; } ;

/* Variables and functions */

__attribute__((used)) static inline int mxcmci_use_dma(struct mxcmci_host *host)
{
	return host->do_dma;
}