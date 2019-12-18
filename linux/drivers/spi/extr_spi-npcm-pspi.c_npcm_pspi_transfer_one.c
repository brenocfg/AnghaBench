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
struct spi_transfer {int dummy; } ;
struct spi_master {int dummy; } ;
struct spi_device {int dummy; } ;
struct npcm_pspi {int /*<<< orphan*/  xfer_done; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  NPCM_PSPI_TIMEOUT_MS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  npcm_pspi_disable (struct npcm_pspi*) ; 
 int /*<<< orphan*/  npcm_pspi_enable (struct npcm_pspi*) ; 
 int /*<<< orphan*/  npcm_pspi_setup_transfer (struct spi_device*,struct spi_transfer*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct npcm_pspi* spi_master_get_devdata (struct spi_master*) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_pspi_transfer_one(struct spi_master *master,
				  struct spi_device *spi,
				  struct spi_transfer *t)
{
	struct npcm_pspi *priv = spi_master_get_devdata(master);
	int status;

	npcm_pspi_setup_transfer(spi, t);
	reinit_completion(&priv->xfer_done);
	npcm_pspi_enable(priv);
	status = wait_for_completion_timeout(&priv->xfer_done,
					     msecs_to_jiffies
					     (NPCM_PSPI_TIMEOUT_MS));
	if (status == 0) {
		npcm_pspi_disable(priv);
		return -ETIMEDOUT;
	}

	return 0;
}