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
struct ahd_softc {int /*<<< orphan*/  dev_softc; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  request_region (scalar_t__,int,char*) ; 

__attribute__((used)) static int
ahd_linux_pci_reserve_io_regions(struct ahd_softc *ahd, resource_size_t *base,
				 resource_size_t *base2)
{
	*base = pci_resource_start(ahd->dev_softc, 0);
	/*
	 * This is really the 3rd bar and should be at index 2,
	 * but the Linux PCI code doesn't know how to "count" 64bit
	 * bars.
	 */
	*base2 = pci_resource_start(ahd->dev_softc, 3);
	if (*base == 0 || *base2 == 0)
		return (ENOMEM);
	if (!request_region(*base, 256, "aic79xx"))
		return (ENOMEM);
	if (!request_region(*base2, 256, "aic79xx")) {
		release_region(*base, 256);
		return (ENOMEM);
	}
	return (0);
}