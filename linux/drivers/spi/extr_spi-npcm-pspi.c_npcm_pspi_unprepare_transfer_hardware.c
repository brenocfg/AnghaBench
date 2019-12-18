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
struct spi_master {int dummy; } ;
struct npcm_pspi {int dummy; } ;

/* Variables and functions */
 int NPCM_PSPI_CTL1_EIR ; 
 int NPCM_PSPI_CTL1_EIW ; 
 int /*<<< orphan*/  npcm_pspi_irq_disable (struct npcm_pspi*,int) ; 
 struct npcm_pspi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int npcm_pspi_unprepare_transfer_hardware(struct spi_master *master)
{
	struct npcm_pspi *priv = spi_master_get_devdata(master);

	npcm_pspi_irq_disable(priv, NPCM_PSPI_CTL1_EIR | NPCM_PSPI_CTL1_EIW);

	return 0;
}