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
typedef  int u16 ;
struct spi_device {int mode; int /*<<< orphan*/  master; } ;
struct npcm_pspi {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ NPCM_PSPI_CTL1 ; 
 int NPCM_PSPI_CTL1_SCIDL ; 
 int NPCM_PSPI_CTL1_SCM ; 
 int SPI_CPHA ; 
 int SPI_CPOL ; 
#define  SPI_MODE_0 131 
#define  SPI_MODE_1 130 
#define  SPI_MODE_2 129 
#define  SPI_MODE_3 128 
 int ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 struct npcm_pspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm_pspi_set_mode(struct spi_device *spi)
{
	struct npcm_pspi *priv = spi_master_get_devdata(spi->master);
	u16 regtemp;
	u16 mode_val;

	switch (spi->mode & (SPI_CPOL | SPI_CPHA)) {
	case SPI_MODE_0:
		mode_val = 0;
		break;
	case SPI_MODE_1:
		mode_val = NPCM_PSPI_CTL1_SCIDL;
		break;
	case SPI_MODE_2:
		mode_val = NPCM_PSPI_CTL1_SCM;
		break;
	case SPI_MODE_3:
		mode_val = NPCM_PSPI_CTL1_SCIDL | NPCM_PSPI_CTL1_SCM;
		break;
	}

	regtemp = ioread16(priv->base + NPCM_PSPI_CTL1);
	regtemp &= ~(NPCM_PSPI_CTL1_SCM | NPCM_PSPI_CTL1_SCIDL);
	iowrite16(regtemp | mode_val, priv->base + NPCM_PSPI_CTL1);
}