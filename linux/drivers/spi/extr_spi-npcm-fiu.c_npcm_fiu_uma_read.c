#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_10__ {int nbytes; int /*<<< orphan*/  buswidth; } ;
struct TYPE_9__ {int nbytes; int /*<<< orphan*/  buswidth; } ;
struct TYPE_8__ {int /*<<< orphan*/  buswidth; } ;
struct TYPE_7__ {int opcode; int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_5__ addr; TYPE_4__ dummy; TYPE_3__ data; TYPE_2__ cmd; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct npcm_fiu_spi {int /*<<< orphan*/  regmap; } ;
struct TYPE_6__ {int chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int BIT (int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_ADDR ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_CFG ; 
 int NPCM_FIU_UMA_CFG_ADBPCK_SHIFT ; 
 int NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT ; 
 int NPCM_FIU_UMA_CFG_DBPCK_SHIFT ; 
 int NPCM_FIU_UMA_CFG_DBSIZ_SHIFT ; 
 int NPCM_FIU_UMA_CFG_RDATSIZ_SHIFT ; 
 int NPCM_FIU_UMA_CFG_RDBPCK_SHIFT ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_CMD ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_CMD_CMD ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_CTS ; 
 int /*<<< orphan*/  NPCM_FIU_UMA_CTS_DEV_NUM ; 
 int NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT ; 
 int NPCM_FIU_UMA_CTS_EXEC_DONE ; 
 scalar_t__ NPCM_FIU_UMA_DR0 ; 
 int /*<<< orphan*/  UMA_MICRO_SEC_TIMEOUT ; 
 int ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct npcm_fiu_spi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_fiu_uma_read(struct spi_mem *mem,
			     const struct spi_mem_op *op, u32 addr,
			      bool is_address_size, u8 *data, u32 data_size)
{
	struct npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	u32 uma_cfg = BIT(10);
	u32 data_reg[4];
	int ret;
	u32 val;
	u32 i;

	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			   NPCM_FIU_UMA_CTS_DEV_NUM,
			   (mem->spi->chip_select <<
			    NPCM_FIU_UMA_CTS_DEV_NUM_SHIFT));
	regmap_update_bits(fiu->regmap, NPCM_FIU_UMA_CMD,
			   NPCM_FIU_UMA_CMD_CMD, op->cmd.opcode);

	if (is_address_size) {
		uma_cfg |= ilog2(op->cmd.buswidth);
		uma_cfg |= ilog2(op->addr.buswidth)
			<< NPCM_FIU_UMA_CFG_ADBPCK_SHIFT;
		uma_cfg |= ilog2(op->dummy.buswidth)
			<< NPCM_FIU_UMA_CFG_DBPCK_SHIFT;
		uma_cfg |= ilog2(op->data.buswidth)
			<< NPCM_FIU_UMA_CFG_RDBPCK_SHIFT;
		uma_cfg |= op->dummy.nbytes << NPCM_FIU_UMA_CFG_DBSIZ_SHIFT;
		uma_cfg |= op->addr.nbytes << NPCM_FIU_UMA_CFG_ADDSIZ_SHIFT;
		regmap_write(fiu->regmap, NPCM_FIU_UMA_ADDR, addr);
	} else {
		regmap_write(fiu->regmap, NPCM_FIU_UMA_ADDR, 0x0);
	}

	uma_cfg |= data_size << NPCM_FIU_UMA_CFG_RDATSIZ_SHIFT;
	regmap_write(fiu->regmap, NPCM_FIU_UMA_CFG, uma_cfg);
	regmap_write_bits(fiu->regmap, NPCM_FIU_UMA_CTS,
			  NPCM_FIU_UMA_CTS_EXEC_DONE,
			  NPCM_FIU_UMA_CTS_EXEC_DONE);
	ret = regmap_read_poll_timeout(fiu->regmap, NPCM_FIU_UMA_CTS, val,
				       (!(val & NPCM_FIU_UMA_CTS_EXEC_DONE)), 0,
				       UMA_MICRO_SEC_TIMEOUT);
	if (ret)
		return ret;

	if (data_size) {
		for (i = 0; i < DIV_ROUND_UP(data_size, 4); i++)
			regmap_read(fiu->regmap, NPCM_FIU_UMA_DR0 + (i * 4),
				    &data_reg[i]);
		memcpy(data, data_reg, data_size);
	}

	return 0;
}