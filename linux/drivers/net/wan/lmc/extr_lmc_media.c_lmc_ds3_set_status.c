#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ scrambler_onoff; scalar_t__ cable_length; } ;
struct TYPE_15__ {TYPE_2__ ictl; TYPE_1__* lmc_media; } ;
typedef  TYPE_3__ lmc_softc_t ;
struct TYPE_16__ {scalar_t__ scrambler_onoff; scalar_t__ cable_length; } ;
typedef  TYPE_4__ lmc_ctl_t ;
struct TYPE_13__ {int /*<<< orphan*/  (* set_scrambler ) (TYPE_3__* const,scalar_t__) ;int /*<<< orphan*/  (* set_cable_length ) (TYPE_3__* const,scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CABLE_LENGTH_GT_100FT ; 
 int /*<<< orphan*/  LMC_CTL_CABLE_LENGTH_LT_100FT ; 
 int /*<<< orphan*/  LMC_CTL_OFF ; 
 int /*<<< orphan*/  LMC_CTL_ON ; 
 int /*<<< orphan*/  lmc_ds3_set_100ft (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmc_ds3_set_scram (TYPE_3__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lmc_set_protocol (TYPE_3__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__* const,scalar_t__) ; 

__attribute__((used)) static void
lmc_ds3_set_status (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
  if (ctl == NULL)
    {
      sc->lmc_media->set_cable_length (sc, sc->ictl.cable_length);
      sc->lmc_media->set_scrambler (sc, sc->ictl.scrambler_onoff);
      lmc_set_protocol (sc, NULL);

      return;
    }

  /*
   * check for change in cable length setting
   */
  if (ctl->cable_length && !sc->ictl.cable_length)
    lmc_ds3_set_100ft (sc, LMC_CTL_CABLE_LENGTH_GT_100FT);
  else if (!ctl->cable_length && sc->ictl.cable_length)
    lmc_ds3_set_100ft (sc, LMC_CTL_CABLE_LENGTH_LT_100FT);

  /*
   * Check for change in scrambler setting (requires reset)
   */
  if (ctl->scrambler_onoff && !sc->ictl.scrambler_onoff)
    lmc_ds3_set_scram (sc, LMC_CTL_ON);
  else if (!ctl->scrambler_onoff && sc->ictl.scrambler_onoff)
    lmc_ds3_set_scram (sc, LMC_CTL_OFF);

  lmc_set_protocol (sc, ctl);
}