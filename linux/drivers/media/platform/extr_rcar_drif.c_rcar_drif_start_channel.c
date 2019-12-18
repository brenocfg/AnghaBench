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
typedef  int u32 ;
struct rcar_drif_sdr {int dummy; } ;
struct rcar_drif {int /*<<< orphan*/  num; scalar_t__ base; struct rcar_drif_sdr* sdr; } ;

/* Variables and functions */
 int RCAR_DRIF_REOF ; 
 int RCAR_DRIF_RFFUL ; 
 int RCAR_DRIF_RFOVF ; 
 int RCAR_DRIF_RFSERR ; 
 int RCAR_DRIF_RFUDF ; 
 scalar_t__ RCAR_DRIF_SICTR ; 
 int RCAR_DRIF_SICTR_RESET ; 
 scalar_t__ RCAR_DRIF_SIIER ; 
 scalar_t__ RCAR_DRIF_SISTR ; 
 int rcar_drif_qbuf (struct rcar_drif*) ; 
 int /*<<< orphan*/  rcar_drif_read (struct rcar_drif*,scalar_t__) ; 
 int /*<<< orphan*/  rcar_drif_write (struct rcar_drif*,scalar_t__,int) ; 
 int /*<<< orphan*/  rdrif_err (struct rcar_drif_sdr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int readl_poll_timeout (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int rcar_drif_start_channel(struct rcar_drif *ch)
{
	struct rcar_drif_sdr *sdr = ch->sdr;
	u32 ctr, str;
	int ret;

	/* Reset receive */
	rcar_drif_write(ch, RCAR_DRIF_SICTR, RCAR_DRIF_SICTR_RESET);
	ret = readl_poll_timeout(ch->base + RCAR_DRIF_SICTR, ctr,
				 !(ctr & RCAR_DRIF_SICTR_RESET), 7, 100000);
	if (ret) {
		rdrif_err(sdr, "ch%u: failed to reset rx. ctr 0x%08x\n",
			  ch->num, rcar_drif_read(ch, RCAR_DRIF_SICTR));
		return ret;
	}

	/* Queue buffers for DMA */
	ret = rcar_drif_qbuf(ch);
	if (ret)
		return ret;

	/* Clear status register flags */
	str = RCAR_DRIF_RFFUL | RCAR_DRIF_REOF | RCAR_DRIF_RFSERR |
		RCAR_DRIF_RFUDF | RCAR_DRIF_RFOVF;
	rcar_drif_write(ch, RCAR_DRIF_SISTR, str);

	/* Enable DMA receive interrupt */
	rcar_drif_write(ch, RCAR_DRIF_SIIER, 0x00009000);

	return ret;
}