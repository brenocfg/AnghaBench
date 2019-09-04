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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nitrox_cleanup_pkt_slc_bh (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_disable_msix (struct nitrox_device*) ; 

void nitrox_pf_cleanup_isr(struct nitrox_device *ndev)
{
	nitrox_disable_msix(ndev);
	nitrox_cleanup_pkt_slc_bh(ndev);
}