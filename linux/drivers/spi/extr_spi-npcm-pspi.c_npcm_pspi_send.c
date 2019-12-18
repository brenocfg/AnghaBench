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
struct npcm_pspi {int tx_bytes; int /*<<< orphan*/ * tx_buf; scalar_t__ base; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 scalar_t__ NPCM_PSPI_DATA ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npcm_pspi_send(struct npcm_pspi *priv)
{
	int wsize;

	wsize = min(bytes_per_word(priv->bits_per_word), priv->tx_bytes);
	priv->tx_bytes -= wsize;

	if (!priv->tx_buf)
		return;

	switch (wsize) {
	case 1:
		iowrite8(*priv->tx_buf, NPCM_PSPI_DATA + priv->base);
		break;
	case 2:
		iowrite16(*priv->tx_buf, NPCM_PSPI_DATA + priv->base);
		break;
	default:
		WARN_ON_ONCE(1);
		return;
	}

	priv->tx_buf += wsize;
}