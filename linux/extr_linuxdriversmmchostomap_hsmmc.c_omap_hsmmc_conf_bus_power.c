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
typedef  int u32 ;
struct omap_hsmmc_host {int /*<<< orphan*/  base; TYPE_1__* pdata; } ;
struct TYPE_2__ {int controller_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAPA ; 
 int /*<<< orphan*/  HCTL ; 
 int OMAP_HSMMC_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OMAP_HSMMC_SUPPORTS_DUAL_VOLT ; 
 int /*<<< orphan*/  OMAP_HSMMC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int SDVS18 ; 
 int SDVS30 ; 
 int SDVS_MASK ; 
 int VS18 ; 
 int VS30 ; 
 int /*<<< orphan*/  set_sd_bus_power (struct omap_hsmmc_host*) ; 

__attribute__((used)) static void omap_hsmmc_conf_bus_power(struct omap_hsmmc_host *host)
{
	u32 hctl, capa, value;

	/* Only MMC1 supports 3.0V */
	if (host->pdata->controller_flags & OMAP_HSMMC_SUPPORTS_DUAL_VOLT) {
		hctl = SDVS30;
		capa = VS30 | VS18;
	} else {
		hctl = SDVS18;
		capa = VS18;
	}

	value = OMAP_HSMMC_READ(host->base, HCTL) & ~SDVS_MASK;
	OMAP_HSMMC_WRITE(host->base, HCTL, value | hctl);

	value = OMAP_HSMMC_READ(host->base, CAPA);
	OMAP_HSMMC_WRITE(host->base, CAPA, value | capa);

	/* Set SD bus power bit */
	set_sd_bus_power(host);
}