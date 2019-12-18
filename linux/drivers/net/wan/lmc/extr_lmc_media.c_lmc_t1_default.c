#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  clock_source; } ;
struct TYPE_10__ {TYPE_2__ ictl; TYPE_1__* lmc_media; int /*<<< orphan*/  lmc_miireg16; } ;
typedef  TYPE_3__ lmc_softc_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_crc_length ) (TYPE_3__* const,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_circuit_type ) (TYPE_3__* const,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_link_status ) (TYPE_3__* const,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CIRCUIT_TYPE_T1 ; 
 int /*<<< orphan*/  LMC_CTL_CLOCK_SOURCE_INT ; 
 int /*<<< orphan*/  LMC_CTL_CRC_LENGTH_16 ; 
 int /*<<< orphan*/  LMC_LINK_DOWN ; 
 int /*<<< orphan*/  LMC_MII16_LED_ALL ; 
 int /*<<< orphan*/  stub1 (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lmc_t1_default (lmc_softc_t * const sc)
{
  sc->lmc_miireg16 = LMC_MII16_LED_ALL;
  sc->lmc_media->set_link_status (sc, LMC_LINK_DOWN);
  sc->lmc_media->set_circuit_type (sc, LMC_CTL_CIRCUIT_TYPE_T1);
  sc->lmc_media->set_crc_length (sc, LMC_CTL_CRC_LENGTH_16);
  /* Right now we can only clock from out internal source */
  sc->ictl.clock_source = LMC_CTL_CLOCK_SOURCE_INT;
}