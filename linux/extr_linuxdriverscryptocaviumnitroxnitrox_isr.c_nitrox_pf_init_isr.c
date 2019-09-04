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
 int nitrox_enable_msix (struct nitrox_device*) ; 
 int nitrox_request_irqs (struct nitrox_device*) ; 
 int nitrox_setup_pkt_slc_bh (struct nitrox_device*) ; 

int nitrox_pf_init_isr(struct nitrox_device *ndev)
{
	int err;

	err = nitrox_setup_pkt_slc_bh(ndev);
	if (err)
		return err;

	err = nitrox_enable_msix(ndev);
	if (err)
		goto msix_fail;

	err = nitrox_request_irqs(ndev);
	if (err)
		goto irq_fail;

	return 0;

irq_fail:
	nitrox_disable_msix(ndev);
msix_fail:
	nitrox_cleanup_pkt_slc_bh(ndev);
	return err;
}