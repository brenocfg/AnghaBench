#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int u32 ;
struct spi_nor {int /*<<< orphan*/  program_opcode; struct nxp_spifi* priv; } ;
struct TYPE_2__ {scalar_t__ addr_width; } ;
struct nxp_spifi {scalar_t__ io_base; TYPE_1__ nor; } ;
typedef  int ssize_t ;
typedef  int loff_t ;

/* Variables and functions */
 scalar_t__ SPIFI_ADDR ; 
 scalar_t__ SPIFI_CMD ; 
 int SPIFI_CMD_DATALEN (size_t) ; 
 int SPIFI_CMD_DOUT ; 
 int SPIFI_CMD_FIELDFORM_ALL_SERIAL ; 
 int SPIFI_CMD_FRAMEFORM (scalar_t__) ; 
 int SPIFI_CMD_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFI_DATA ; 
 int nxp_spifi_set_memory_mode_off (struct nxp_spifi*) ; 
 int nxp_spifi_wait_for_cmd (struct nxp_spifi*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static ssize_t nxp_spifi_write(struct spi_nor *nor, loff_t to, size_t len,
			       const u_char *buf)
{
	struct nxp_spifi *spifi = nor->priv;
	u32 cmd;
	int ret;
	size_t i;

	ret = nxp_spifi_set_memory_mode_off(spifi);
	if (ret)
		return ret;

	writel(to, spifi->io_base + SPIFI_ADDR);

	cmd = SPIFI_CMD_DOUT |
	      SPIFI_CMD_DATALEN(len) |
	      SPIFI_CMD_FIELDFORM_ALL_SERIAL |
	      SPIFI_CMD_OPCODE(nor->program_opcode) |
	      SPIFI_CMD_FRAMEFORM(spifi->nor.addr_width + 1);
	writel(cmd, spifi->io_base + SPIFI_CMD);

	for (i = 0; i < len; i++)
		writeb(buf[i], spifi->io_base + SPIFI_DATA);

	ret = nxp_spifi_wait_for_cmd(spifi);
	if (ret)
		return ret;

	return len;
}