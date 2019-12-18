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
typedef  int u8 ;
typedef  int u32 ;
struct spi_transfer {int* tx_buf; int* rx_buf; int len; } ;
struct device {int dummy; } ;
struct spi_device {int chip_select; int /*<<< orphan*/  master; struct device dev; } ;
struct falcon_sflash {int sfcmd; } ;

/* Variables and functions */
 int EBADE ; 
 int ENODATA ; 
 unsigned long FALCON_SPI_XFER_BEGIN ; 
 unsigned long FALCON_SPI_XFER_END ; 
 int /*<<< orphan*/  SFADDR ; 
 int /*<<< orphan*/  SFCMD ; 
 int SFCMD_ALEN_MASK ; 
 unsigned int SFCMD_ALEN_OFFSET ; 
 int SFCMD_CS_MASK ; 
 int SFCMD_CS_OFFSET ; 
 int SFCMD_DIR_WRITE ; 
 unsigned int SFCMD_DLEN_OFFSET ; 
 int SFCMD_DUMLEN_MASK ; 
 unsigned int SFCMD_DUMLEN_OFFSET ; 
 int SFCMD_KEEP_CS_KEEP_SELECTED ; 
 int SFCMD_OPC_MASK ; 
 int /*<<< orphan*/  SFDATA ; 
 int /*<<< orphan*/  SFSTAT ; 
 int SFSTAT_CMD_ERR ; 
 int SFSTAT_CMD_PEND ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int ltq_ebu_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_ebu_w32 (int,int /*<<< orphan*/ ) ; 
 struct falcon_sflash* spi_master_get_devdata (int /*<<< orphan*/ ) ; 

int falcon_sflash_xfer(struct spi_device *spi, struct spi_transfer *t,
		unsigned long flags)
{
	struct device *dev = &spi->dev;
	struct falcon_sflash *priv = spi_master_get_devdata(spi->master);
	const u8 *txp = t->tx_buf;
	u8 *rxp = t->rx_buf;
	unsigned int bytelen = ((8 * t->len + 7) / 8);
	unsigned int len, alen, dumlen;
	u32 val;
	enum {
		state_init,
		state_command_prepare,
		state_write,
		state_read,
		state_disable_cs,
		state_end
	} state = state_init;

	do {
		switch (state) {
		case state_init: /* detect phase of upper layer sequence */
		{
			/* initial write ? */
			if (flags & FALCON_SPI_XFER_BEGIN) {
				if (!txp) {
					dev_err(dev,
						"BEGIN without tx data!\n");
					return -ENODATA;
				}
				/*
				 * Prepare the parts of the sfcmd register,
				 * which should not change during a sequence!
				 * Only exception are the length fields,
				 * especially alen and dumlen.
				 */

				priv->sfcmd = ((spi->chip_select
						<< SFCMD_CS_OFFSET)
					       & SFCMD_CS_MASK);
				priv->sfcmd |= SFCMD_KEEP_CS_KEEP_SELECTED;
				priv->sfcmd |= *txp;
				txp++;
				bytelen--;
				if (bytelen) {
					/*
					 * more data:
					 * maybe address and/or dummy
					 */
					state = state_command_prepare;
					break;
				} else {
					dev_dbg(dev, "write cmd %02X\n",
						priv->sfcmd & SFCMD_OPC_MASK);
				}
			}
			/* continued write ? */
			if (txp && bytelen) {
				state = state_write;
				break;
			}
			/* read data? */
			if (rxp && bytelen) {
				state = state_read;
				break;
			}
			/* end of sequence? */
			if (flags & FALCON_SPI_XFER_END)
				state = state_disable_cs;
			else
				state = state_end;
			break;
		}
		/* collect tx data for address and dummy phase */
		case state_command_prepare:
		{
			/* txp is valid, already checked */
			val = 0;
			alen = 0;
			dumlen = 0;
			while (bytelen > 0) {
				if (alen < 3) {
					val = (val << 8) | (*txp++);
					alen++;
				} else if ((dumlen < 15) && (*txp == 0)) {
					/*
					 * assume dummy bytes are set to 0
					 * from upper layer
					 */
					dumlen++;
					txp++;
				} else {
					break;
				}
				bytelen--;
			}
			priv->sfcmd &= ~(SFCMD_ALEN_MASK | SFCMD_DUMLEN_MASK);
			priv->sfcmd |= (alen << SFCMD_ALEN_OFFSET) |
					 (dumlen << SFCMD_DUMLEN_OFFSET);
			if (alen > 0)
				ltq_ebu_w32(val, SFADDR);

			dev_dbg(dev, "wr %02X, alen=%d (addr=%06X) dlen=%d\n",
				priv->sfcmd & SFCMD_OPC_MASK,
				alen, val, dumlen);

			if (bytelen > 0) {
				/* continue with write */
				state = state_write;
			} else if (flags & FALCON_SPI_XFER_END) {
				/* end of sequence? */
				state = state_disable_cs;
			} else {
				/*
				 * go to end and expect another
				 * call (read or write)
				 */
				state = state_end;
			}
			break;
		}
		case state_write:
		{
			/* txp still valid */
			priv->sfcmd |= SFCMD_DIR_WRITE;
			len = 0;
			val = 0;
			do {
				if (bytelen--)
					val |= (*txp++) << (8 * len++);
				if ((flags & FALCON_SPI_XFER_END)
				    && (bytelen == 0)) {
					priv->sfcmd &=
						~SFCMD_KEEP_CS_KEEP_SELECTED;
				}
				if ((len == 4) || (bytelen == 0)) {
					ltq_ebu_w32(val, SFDATA);
					ltq_ebu_w32(priv->sfcmd
						| (len<<SFCMD_DLEN_OFFSET),
						SFCMD);
					len = 0;
					val = 0;
					priv->sfcmd &= ~(SFCMD_ALEN_MASK
							 | SFCMD_DUMLEN_MASK);
				}
			} while (bytelen);
			state = state_end;
			break;
		}
		case state_read:
		{
			/* read data */
			priv->sfcmd &= ~SFCMD_DIR_WRITE;
			do {
				if ((flags & FALCON_SPI_XFER_END)
				    && (bytelen <= 4)) {
					priv->sfcmd &=
						~SFCMD_KEEP_CS_KEEP_SELECTED;
				}
				len = (bytelen > 4) ? 4 : bytelen;
				bytelen -= len;
				ltq_ebu_w32(priv->sfcmd
					| (len << SFCMD_DLEN_OFFSET), SFCMD);
				priv->sfcmd &= ~(SFCMD_ALEN_MASK
						 | SFCMD_DUMLEN_MASK);
				do {
					val = ltq_ebu_r32(SFSTAT);
					if (val & SFSTAT_CMD_ERR) {
						/* reset error status */
						dev_err(dev, "SFSTAT: CMD_ERR");
						dev_err(dev, " (%x)\n", val);
						ltq_ebu_w32(SFSTAT_CMD_ERR,
							SFSTAT);
						return -EBADE;
					}
				} while (val & SFSTAT_CMD_PEND);
				val = ltq_ebu_r32(SFDATA);
				do {
					*rxp = (val & 0xFF);
					rxp++;
					val >>= 8;
					len--;
				} while (len);
			} while (bytelen);
			state = state_end;
			break;
		}
		case state_disable_cs:
		{
			priv->sfcmd &= ~SFCMD_KEEP_CS_KEEP_SELECTED;
			ltq_ebu_w32(priv->sfcmd | (0 << SFCMD_DLEN_OFFSET),
				SFCMD);
			val = ltq_ebu_r32(SFSTAT);
			if (val & SFSTAT_CMD_ERR) {
				/* reset error status */
				dev_err(dev, "SFSTAT: CMD_ERR (%x)\n", val);
				ltq_ebu_w32(SFSTAT_CMD_ERR, SFSTAT);
				return -EBADE;
			}
			state = state_end;
			break;
		}
		case state_end:
			break;
		}
	} while (state != state_end);

	return 0;
}