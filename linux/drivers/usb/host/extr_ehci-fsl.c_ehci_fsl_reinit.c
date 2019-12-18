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
struct ehci_hcd {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ehci_fsl_usb_setup (struct ehci_hcd*) ; 

__attribute__((used)) static int ehci_fsl_reinit(struct ehci_hcd *ehci)
{
	if (ehci_fsl_usb_setup(ehci))
		return -EINVAL;

	return 0;
}