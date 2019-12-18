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
typedef  int /*<<< orphan*/  u_long ;
struct pci_dev {int dummy; } ;
struct ahc_softc {TYPE_1__* platform_data; } ;
struct TYPE_2__ {scalar_t__ host; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  ahc_free (struct ahc_softc*) ; 
 int /*<<< orphan*/  ahc_intr_enable (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_lock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ahc_unlock (struct ahc_softc*,int /*<<< orphan*/ *) ; 
 struct ahc_softc* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  scsi_remove_host (scalar_t__) ; 

__attribute__((used)) static void
ahc_linux_pci_dev_remove(struct pci_dev *pdev)
{
	struct ahc_softc *ahc = pci_get_drvdata(pdev);
	u_long s;

	if (ahc->platform_data && ahc->platform_data->host)
			scsi_remove_host(ahc->platform_data->host);

	ahc_lock(ahc, &s);
	ahc_intr_enable(ahc, FALSE);
	ahc_unlock(ahc, &s);
	ahc_free(ahc);
}