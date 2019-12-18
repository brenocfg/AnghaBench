#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int crc_length; } ;
struct TYPE_6__ {int /*<<< orphan*/  lmc_miireg16; int /*<<< orphan*/  lmc_crcSize; TYPE_1__ ictl; } ;
typedef  TYPE_2__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CRC_BYTESIZE_2 ; 
 int /*<<< orphan*/  LMC_CTL_CRC_BYTESIZE_4 ; 
 int LMC_CTL_CRC_LENGTH_16 ; 
 int LMC_CTL_CRC_LENGTH_32 ; 
 int /*<<< orphan*/  LMC_MII16_SSI_CRC ; 
 int /*<<< orphan*/  lmc_mii_writereg (TYPE_2__* const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lmc_ssi_set_crc_length (lmc_softc_t * const sc, int state)
{
  if (state == LMC_CTL_CRC_LENGTH_32)
    {
      /* 32 bit */
      sc->lmc_miireg16 |= LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_32;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_4;

    }
  else
    {
      /* 16 bit */
      sc->lmc_miireg16 &= ~LMC_MII16_SSI_CRC;
      sc->ictl.crc_length = LMC_CTL_CRC_LENGTH_16;
      sc->lmc_crcSize = LMC_CTL_CRC_BYTESIZE_2;
    }

  lmc_mii_writereg (sc, 0, 16, sc->lmc_miireg16);
}