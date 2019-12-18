#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct spi_nor {TYPE_2__* info; } ;
struct TYPE_4__ {TYPE_1__* fixups; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* default_init ) (struct spi_nor*) ;} ;

/* Variables and functions */
 int JEDEC_MFR (TYPE_2__*) ; 
#define  SNOR_MFR_MACRONIX 131 
#define  SNOR_MFR_MICRON 130 
#define  SNOR_MFR_ST 129 
#define  SNOR_MFR_WINBOND 128 
 int /*<<< orphan*/  macronix_set_default_init (struct spi_nor*) ; 
 int /*<<< orphan*/  st_micron_set_default_init (struct spi_nor*) ; 
 int /*<<< orphan*/  stub1 (struct spi_nor*) ; 
 int /*<<< orphan*/  winbond_set_default_init (struct spi_nor*) ; 

__attribute__((used)) static void spi_nor_manufacturer_init_params(struct spi_nor *nor)
{
	/* Init flash parameters based on MFR */
	switch (JEDEC_MFR(nor->info)) {
	case SNOR_MFR_MACRONIX:
		macronix_set_default_init(nor);
		break;

	case SNOR_MFR_ST:
	case SNOR_MFR_MICRON:
		st_micron_set_default_init(nor);
		break;

	case SNOR_MFR_WINBOND:
		winbond_set_default_init(nor);
		break;

	default:
		break;
	}

	if (nor->info->fixups && nor->info->fixups->default_init)
		nor->info->fixups->default_init(nor);
}