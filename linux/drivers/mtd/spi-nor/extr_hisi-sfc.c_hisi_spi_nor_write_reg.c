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
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {struct hifmc_priv* priv; } ;
struct hifmc_priv {struct hifmc_host* host; } ;
struct hifmc_host {int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMC_OP_WRITE_DATA_EN ; 
 int hisi_spi_nor_op_reg (struct spi_nor*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int hisi_spi_nor_write_reg(struct spi_nor *nor, u8 opcode,
				u8 *buf, int len)
{
	struct hifmc_priv *priv = nor->priv;
	struct hifmc_host *host = priv->host;

	if (len)
		memcpy_toio(host->iobase, buf, len);

	return hisi_spi_nor_op_reg(nor, opcode, len, FMC_OP_WRITE_DATA_EN);
}