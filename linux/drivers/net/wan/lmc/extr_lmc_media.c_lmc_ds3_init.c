#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cardtype; } ;
struct TYPE_7__ {TYPE_1__ ictl; } ;
typedef  TYPE_2__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CARDTYPE_LMC5245 ; 
 int /*<<< orphan*/  lmc_mii_readreg (TYPE_2__* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lmc_mii_writereg (TYPE_2__* const,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
lmc_ds3_init (lmc_softc_t * const sc)
{
  int i;

  sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC5245;

  /* writes zeros everywhere */
  for (i = 0; i < 21; i++)
    {
      lmc_mii_writereg (sc, 0, 17, i);
      lmc_mii_writereg (sc, 0, 18, 0);
    }

  /* set some essential bits */
  lmc_mii_writereg (sc, 0, 17, 1);
  lmc_mii_writereg (sc, 0, 18, 0x25);	/* ser, xtx */

  lmc_mii_writereg (sc, 0, 17, 5);
  lmc_mii_writereg (sc, 0, 18, 0x80);	/* emode */

  lmc_mii_writereg (sc, 0, 17, 14);
  lmc_mii_writereg (sc, 0, 18, 0x30);	/* rcgen, tcgen */

  /* clear counters and latched bits */
  for (i = 0; i < 21; i++)
    {
      lmc_mii_writereg (sc, 0, 17, i);
      lmc_mii_readreg (sc, 0, 18);
    }
}