#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ circuit_type; } ;
struct TYPE_14__ {TYPE_1__* lmc_media; TYPE_2__ ictl; } ;
typedef  TYPE_3__ lmc_softc_t ;
struct TYPE_15__ {scalar_t__ circuit_type; } ;
typedef  TYPE_4__ lmc_ctl_t ;
struct TYPE_12__ {int /*<<< orphan*/  (* set_circuit_type ) (TYPE_3__* const,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ LMC_CTL_CIRCUIT_TYPE_E1 ; 
 scalar_t__ LMC_CTL_CIRCUIT_TYPE_T1 ; 
 int /*<<< orphan*/  lmc_set_protocol (TYPE_3__* const,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__* const,scalar_t__) ; 

__attribute__((used)) static void
lmc_t1_set_status (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
  if (ctl == NULL)
    {
      sc->lmc_media->set_circuit_type (sc, sc->ictl.circuit_type);
      lmc_set_protocol (sc, NULL);

      return;
    }
  /*
   * check for change in circuit type         */
  if (ctl->circuit_type == LMC_CTL_CIRCUIT_TYPE_T1
      && sc->ictl.circuit_type ==
      LMC_CTL_CIRCUIT_TYPE_E1) sc->lmc_media->set_circuit_type (sc,
								LMC_CTL_CIRCUIT_TYPE_E1);
  else if (ctl->circuit_type == LMC_CTL_CIRCUIT_TYPE_E1
	   && sc->ictl.circuit_type == LMC_CTL_CIRCUIT_TYPE_T1)
    sc->lmc_media->set_circuit_type (sc, LMC_CTL_CIRCUIT_TYPE_T1);
  lmc_set_protocol (sc, ctl);
}