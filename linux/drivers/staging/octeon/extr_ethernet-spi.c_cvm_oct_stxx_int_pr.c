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
struct TYPE_2__ {scalar_t__ calpar0; scalar_t__ calpar1; scalar_t__ ovrbst; scalar_t__ datovr; scalar_t__ diperr; scalar_t__ nosync; scalar_t__ unxfrm; scalar_t__ frmerr; scalar_t__ syncerr; } ;
union cvmx_stxx_int_reg {TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static void cvm_oct_stxx_int_pr(union cvmx_stxx_int_reg stx_int_reg, int index)
{
	if (stx_int_reg.s.syncerr)
		pr_err("SPI%d: STX Interface encountered a fatal error\n",
		       index);
	if (stx_int_reg.s.frmerr)
		pr_err("SPI%d: STX FRMCNT has exceeded STX_DIP_CNT[MAXFRM]\n",
		       index);
	if (stx_int_reg.s.unxfrm)
		pr_err("SPI%d: STX Unexpected framing sequence\n", index);
	if (stx_int_reg.s.nosync)
		pr_err("SPI%d: STX ERRCNT has exceeded STX_DIP_CNT[MAXDIP]\n",
		       index);
	if (stx_int_reg.s.diperr)
		pr_err("SPI%d: STX DIP2 error on the Spi4 Status channel\n",
		       index);
	if (stx_int_reg.s.datovr)
		pr_err("SPI%d: STX Spi4 FIFO overflow error\n", index);
	if (stx_int_reg.s.ovrbst)
		pr_err("SPI%d: STX Transmit packet burst too big\n", index);
	if (stx_int_reg.s.calpar1)
		pr_err("SPI%d: STX Calendar Table Parity Error Bank%d\n",
		       index, 1);
	if (stx_int_reg.s.calpar0)
		pr_err("SPI%d: STX Calendar Table Parity Error Bank%d\n",
		       index, 0);
}