#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  tag ;
struct TYPE_4__ {int len; } ;
struct mmc_spi_host {TYPE_3__* spi; TYPE_2__* data; TYPE_1__ t; } ;
struct mmc_command {int opcode; unsigned short* resp; int error; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int* status; } ;

/* Variables and functions */
 int EFAULT ; 
 int EILSEQ ; 
 int EINVAL ; 
 int EIO ; 
 int ENOSYS ; 
 int ETIMEDOUT ; 
#define  MMC_RSP_SPI_R1 131 
#define  MMC_RSP_SPI_R1B 130 
#define  MMC_RSP_SPI_R2 129 
#define  MMC_RSP_SPI_R3 128 
 int R1_SPI_ADDRESS ; 
 int R1_SPI_COM_CRC ; 
 int R1_SPI_ERASE_RESET ; 
 int R1_SPI_ERASE_SEQ ; 
 int R1_SPI_ILLEGAL_COMMAND ; 
 int R1_SPI_PARAMETER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 char* maptype (struct mmc_command*) ; 
 int /*<<< orphan*/  mmc_cs_off (struct mmc_spi_host*) ; 
 int mmc_spi_readbytes (struct mmc_spi_host*,int) ; 
 int mmc_spi_resp_type (struct mmc_command*) ; 
 int /*<<< orphan*/  mmc_spi_wait_unbusy (struct mmc_spi_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r1b_timeout ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 

__attribute__((used)) static int mmc_spi_response_get(struct mmc_spi_host *host,
		struct mmc_command *cmd, int cs_on)
{
	u8	*cp = host->data->status;
	u8	*end = cp + host->t.len;
	int	value = 0;
	int	bitshift;
	u8 	leftover = 0;
	unsigned short rotator;
	int 	i;
	char	tag[32];

	snprintf(tag, sizeof(tag), "  ... CMD%d response SPI_%s",
		cmd->opcode, maptype(cmd));

	/* Except for data block reads, the whole response will already
	 * be stored in the scratch buffer.  It's somewhere after the
	 * command and the first byte we read after it.  We ignore that
	 * first byte.  After STOP_TRANSMISSION command it may include
	 * two data bits, but otherwise it's all ones.
	 */
	cp += 8;
	while (cp < end && *cp == 0xff)
		cp++;

	/* Data block reads (R1 response types) may need more data... */
	if (cp == end) {
		cp = host->data->status;
		end = cp+1;

		/* Card sends N(CR) (== 1..8) bytes of all-ones then one
		 * status byte ... and we already scanned 2 bytes.
		 *
		 * REVISIT block read paths use nasty byte-at-a-time I/O
		 * so it can always DMA directly into the target buffer.
		 * It'd probably be better to memcpy() the first chunk and
		 * avoid extra i/o calls...
		 *
		 * Note we check for more than 8 bytes, because in practice,
		 * some SD cards are slow...
		 */
		for (i = 2; i < 16; i++) {
			value = mmc_spi_readbytes(host, 1);
			if (value < 0)
				goto done;
			if (*cp != 0xff)
				goto checkstatus;
		}
		value = -ETIMEDOUT;
		goto done;
	}

checkstatus:
	bitshift = 0;
	if (*cp & 0x80)	{
		/* Houston, we have an ugly card with a bit-shifted response */
		rotator = *cp++ << 8;
		/* read the next byte */
		if (cp == end) {
			value = mmc_spi_readbytes(host, 1);
			if (value < 0)
				goto done;
			cp = host->data->status;
			end = cp+1;
		}
		rotator |= *cp++;
		while (rotator & 0x8000) {
			bitshift++;
			rotator <<= 1;
		}
		cmd->resp[0] = rotator >> 8;
		leftover = rotator;
	} else {
		cmd->resp[0] = *cp++;
	}
	cmd->error = 0;

	/* Status byte: the entire seven-bit R1 response.  */
	if (cmd->resp[0] != 0) {
		if ((R1_SPI_PARAMETER | R1_SPI_ADDRESS)
				& cmd->resp[0])
			value = -EFAULT; /* Bad address */
		else if (R1_SPI_ILLEGAL_COMMAND & cmd->resp[0])
			value = -ENOSYS; /* Function not implemented */
		else if (R1_SPI_COM_CRC & cmd->resp[0])
			value = -EILSEQ; /* Illegal byte sequence */
		else if ((R1_SPI_ERASE_SEQ | R1_SPI_ERASE_RESET)
				& cmd->resp[0])
			value = -EIO;    /* I/O error */
		/* else R1_SPI_IDLE, "it's resetting" */
	}

	switch (mmc_spi_resp_type(cmd)) {

	/* SPI R1B == R1 + busy; STOP_TRANSMISSION (for multiblock reads)
	 * and less-common stuff like various erase operations.
	 */
	case MMC_RSP_SPI_R1B:
		/* maybe we read all the busy tokens already */
		while (cp < end && *cp == 0)
			cp++;
		if (cp == end)
			mmc_spi_wait_unbusy(host, r1b_timeout);
		break;

	/* SPI R2 == R1 + second status byte; SEND_STATUS
	 * SPI R5 == R1 + data byte; IO_RW_DIRECT
	 */
	case MMC_RSP_SPI_R2:
		/* read the next byte */
		if (cp == end) {
			value = mmc_spi_readbytes(host, 1);
			if (value < 0)
				goto done;
			cp = host->data->status;
			end = cp+1;
		}
		if (bitshift) {
			rotator = leftover << 8;
			rotator |= *cp << bitshift;
			cmd->resp[0] |= (rotator & 0xFF00);
		} else {
			cmd->resp[0] |= *cp << 8;
		}
		break;

	/* SPI R3, R4, or R7 == R1 + 4 bytes */
	case MMC_RSP_SPI_R3:
		rotator = leftover << 8;
		cmd->resp[1] = 0;
		for (i = 0; i < 4; i++) {
			cmd->resp[1] <<= 8;
			/* read the next byte */
			if (cp == end) {
				value = mmc_spi_readbytes(host, 1);
				if (value < 0)
					goto done;
				cp = host->data->status;
				end = cp+1;
			}
			if (bitshift) {
				rotator |= *cp++ << bitshift;
				cmd->resp[1] |= (rotator >> 8);
				rotator <<= 8;
			} else {
				cmd->resp[1] |= *cp++;
			}
		}
		break;

	/* SPI R1 == just one status byte */
	case MMC_RSP_SPI_R1:
		break;

	default:
		dev_dbg(&host->spi->dev, "bad response type %04x\n",
				mmc_spi_resp_type(cmd));
		if (value >= 0)
			value = -EINVAL;
		goto done;
	}

	if (value < 0)
		dev_dbg(&host->spi->dev, "%s: resp %04x %08x\n",
			tag, cmd->resp[0], cmd->resp[1]);

	/* disable chipselect on errors and some success cases */
	if (value >= 0 && cs_on)
		return value;
done:
	if (value < 0)
		cmd->error = value;
	mmc_cs_off(host);
	return value;
}