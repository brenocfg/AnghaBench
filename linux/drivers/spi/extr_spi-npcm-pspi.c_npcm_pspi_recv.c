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
typedef  int /*<<< orphan*/  u16 ;
struct npcm_pspi {int rx_bytes; int /*<<< orphan*/ * rx_buf; scalar_t__ base; int /*<<< orphan*/  bits_per_word; } ;

/* Variables and functions */
 scalar_t__ NPCM_PSPI_DATA ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  bytes_per_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  ioread8 (scalar_t__) ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void npcm_pspi_recv(struct npcm_pspi *priv)
{
	int rsize;
	u16 val;

	rsize = min(bytes_per_word(priv->bits_per_word), priv->rx_bytes);
	priv->rx_bytes -= rsize;

	if (!priv->rx_buf)
		return;

	switch (rsize) {
	case 1:
		val = ioread8(priv->base + NPCM_PSPI_DATA);
		break;
	case 2:
		val = ioread16(priv->base + NPCM_PSPI_DATA);
		break;
	default:
		WARN_ON_ONCE(1);
		return;
	}

	*priv->rx_buf = val;
	priv->rx_buf += rsize;
}