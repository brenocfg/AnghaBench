#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_10__ {int* in; scalar_t__ out; } ;
struct TYPE_12__ {int nbytes; scalar_t__ dir; TYPE_4__ buf; int /*<<< orphan*/  buswidth; } ;
struct TYPE_11__ {int val; int nbytes; int /*<<< orphan*/  buswidth; } ;
struct TYPE_9__ {int /*<<< orphan*/  opcode; int /*<<< orphan*/  buswidth; } ;
struct TYPE_8__ {int /*<<< orphan*/  buswidth; } ;
struct spi_mem_op {TYPE_6__ data; TYPE_5__ addr; TYPE_3__ cmd; TYPE_2__ dummy; } ;
struct spi_mem {TYPE_1__* spi; } ;
struct npcm_fiu_spi {scalar_t__ clkrate; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; scalar_t__ spix_mode; struct npcm_fiu_chip* chip; } ;
struct npcm_fiu_chip {scalar_t__ clkrate; } ;
struct TYPE_7__ {size_t chip_select; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ SPI_MEM_DATA_IN ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int npcm_fiu_manualwrite (struct spi_mem*,struct spi_mem_op const*) ; 
 int npcm_fiu_read (struct spi_mem*,struct spi_mem_op const*) ; 
 int npcm_fiu_uma_read (struct spi_mem*,struct spi_mem_op const*,int,int,int*,int) ; 
 int npcm_fiu_uma_write (struct spi_mem*,struct spi_mem_op const*,int /*<<< orphan*/ ,int,int*,int) ; 
 struct npcm_fiu_spi* spi_controller_get_devdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm_fiu_exec_op(struct spi_mem *mem, const struct spi_mem_op *op)
{
	struct npcm_fiu_spi *fiu =
		spi_controller_get_devdata(mem->spi->master);
	struct npcm_fiu_chip *chip = &fiu->chip[mem->spi->chip_select];
	int ret = 0;
	u8 *buf;

	dev_dbg(fiu->dev, "cmd:%#x mode:%d.%d.%d.%d addr:%#llx len:%#x\n",
		op->cmd.opcode, op->cmd.buswidth, op->addr.buswidth,
		op->dummy.buswidth, op->data.buswidth, op->addr.val,
		op->data.nbytes);

	if (fiu->spix_mode || op->addr.nbytes > 4)
		return -ENOTSUPP;

	if (fiu->clkrate != chip->clkrate) {
		ret = clk_set_rate(fiu->clk, chip->clkrate);
		if (ret < 0)
			dev_warn(fiu->dev, "Failed setting %lu frequency, stay at %lu frequency\n",
				 chip->clkrate, fiu->clkrate);
		else
			fiu->clkrate = chip->clkrate;
	}

	if (op->data.dir == SPI_MEM_DATA_IN) {
		if (!op->addr.nbytes) {
			buf = op->data.buf.in;
			ret = npcm_fiu_uma_read(mem, op, op->addr.val, false,
						buf, op->data.nbytes);
		} else {
			ret = npcm_fiu_read(mem, op);
		}
	} else  {
		if (!op->addr.nbytes && !op->data.nbytes)
			ret = npcm_fiu_uma_write(mem, op, op->cmd.opcode, false,
						 NULL, 0);
		if (op->addr.nbytes && !op->data.nbytes) {
			int i;
			u8 buf_addr[4];
			u32 addr = op->addr.val;

			for (i = op->addr.nbytes - 1; i >= 0; i--) {
				buf_addr[i] = addr & 0xff;
				addr >>= 8;
			}
			ret = npcm_fiu_uma_write(mem, op, op->cmd.opcode, false,
						 buf_addr, op->addr.nbytes);
		}
		if (!op->addr.nbytes && op->data.nbytes)
			ret = npcm_fiu_uma_write(mem, op, op->cmd.opcode, false,
						 (u8 *)op->data.buf.out,
						 op->data.nbytes);
		if (op->addr.nbytes && op->data.nbytes)
			ret = npcm_fiu_manualwrite(mem, op);
	}

	return ret;
}