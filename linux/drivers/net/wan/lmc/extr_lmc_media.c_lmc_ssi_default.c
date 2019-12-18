#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* lmc_media; int /*<<< orphan*/  lmc_miireg16; } ;
typedef  TYPE_2__ lmc_softc_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* set_crc_length ) (TYPE_2__* const,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_speed ) (TYPE_2__* const,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_clock_source ) (TYPE_2__* const,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_link_status ) (TYPE_2__* const,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CLOCK_SOURCE_EXT ; 
 int /*<<< orphan*/  LMC_CTL_CRC_LENGTH_16 ; 
 int /*<<< orphan*/  LMC_GEP_SSI_TXCLOCK ; 
 int /*<<< orphan*/  LMC_LINK_DOWN ; 
 int /*<<< orphan*/  LMC_MII16_LED_ALL ; 
 int /*<<< orphan*/  lmc_gpio_mkoutput (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lmc_ssi_default (lmc_softc_t * const sc)
{
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;

  /*
   * make TXCLOCK always be an output
   */
  lmc_gpio_mkoutput (sc, LMC_GEP_SSI_TXCLOCK);

  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
  sc->lmc_media->set_speed (sc, NULL);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
}