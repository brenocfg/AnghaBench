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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u8 ;
struct spi_nor {struct mtk_nor* priv; } ;
struct mtk_nor {scalar_t__ base; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_NOR_PIO_READ_CMD ; 
 scalar_t__ MTK_NOR_RDATA_REG ; 
 int mtk_nor_execute_cmd (struct mtk_nor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_nor_set_addr (struct mtk_nor*,int) ; 
 int /*<<< orphan*/  mtk_nor_set_read_mode (struct mtk_nor*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 

__attribute__((used)) static ssize_t mtk_nor_read(struct spi_nor *nor, loff_t from, size_t length,
			    u_char *buffer)
{
	int i, ret;
	int addr = (int)from;
	u8 *buf = (u8 *)buffer;
	struct mtk_nor *mtk_nor = nor->priv;

	/* set mode for fast read mode ,dual mode or quad mode */
	mtk_nor_set_read_mode(mtk_nor);
	mtk_nor_set_addr(mtk_nor, addr);

	for (i = 0; i < length; i++) {
		ret = mtk_nor_execute_cmd(mtk_nor, MTK_NOR_PIO_READ_CMD);
		if (ret < 0)
			return ret;
		buf[i] = readb(mtk_nor->base + MTK_NOR_RDATA_REG);
	}
	return length;
}