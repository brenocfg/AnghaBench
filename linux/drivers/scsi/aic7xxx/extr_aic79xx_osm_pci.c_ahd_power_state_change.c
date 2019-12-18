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
typedef  int /*<<< orphan*/  ahd_power_state ;

/* Variables and functions */
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ahd_power_state_change(struct ahd_softc *ahd, ahd_power_state new_state)
{
	pci_set_power_state(ahd->dev_softc, new_state);
}