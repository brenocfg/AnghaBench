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
typedef  int u32 ;
struct spi_nor {struct nxp_spifi* priv; } ;
struct nxp_spifi {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ SPIFI_CMD ; 
 int SPIFI_CMD_DATALEN (int) ; 
 int SPIFI_CMD_FIELDFORM_ALL_SERIAL ; 
 int SPIFI_CMD_FRAMEFORM_OPCODE_ONLY ; 
 int SPIFI_CMD_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFI_DATA ; 
 int nxp_spifi_set_memory_mode_off (struct nxp_spifi*) ; 
 int nxp_spifi_wait_for_cmd (struct nxp_spifi*) ; 
 int /*<<< orphan*/  readb (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int nxp_spifi_read_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	struct nxp_spifi *spifi = nor->priv;
	u32 cmd;
	int ret;

	ret = nxp_spifi_set_memory_mode_off(spifi);
	if (ret)
		return ret;

	cmd = SPIFI_CMD_DATALEN(len) |
	      SPIFI_CMD_OPCODE(opcode) |
	      SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_FRAMEFORM_OPCODE_ONLY;
	writel(cmd, spifi->io_base + SPIFI_CMD);

	while (len--)
		*buf++ = readb(spifi->io_base + SPIFI_DATA);

	return nxp_spifi_wait_for_cmd(spifi);
}