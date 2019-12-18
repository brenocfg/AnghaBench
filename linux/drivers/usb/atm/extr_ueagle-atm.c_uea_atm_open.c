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
struct usbatm_data {struct uea_softc* driver_data; } ;
struct uea_softc {int dummy; } ;
struct atm_dev {int /*<<< orphan*/  esi; } ;

/* Variables and functions */
 int uea_getesi (struct uea_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uea_atm_open(struct usbatm_data *usbatm, struct atm_dev *atm_dev)
{
	struct uea_softc *sc = usbatm->driver_data;

	return uea_getesi(sc, atm_dev->esi);
}