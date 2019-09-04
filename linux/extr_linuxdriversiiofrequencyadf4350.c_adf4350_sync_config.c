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
typedef  int u32 ;
struct adf4350_state {int* regs_hw; int* regs; TYPE_1__* spi; int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ADF4350_REG0 ; 
#define  ADF4350_REG1 129 
#define  ADF4350_REG4 128 
 int ADF4350_REG5 ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int spi_write (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adf4350_sync_config(struct adf4350_state *st)
{
	int ret, i, doublebuf = 0;

	for (i = ADF4350_REG5; i >= ADF4350_REG0; i--) {
		if ((st->regs_hw[i] != st->regs[i]) ||
			((i == ADF4350_REG0) && doublebuf)) {
			switch (i) {
			case ADF4350_REG1:
			case ADF4350_REG4:
				doublebuf = 1;
				break;
			}

			st->val  = cpu_to_be32(st->regs[i] | i);
			ret = spi_write(st->spi, &st->val, 4);
			if (ret < 0)
				return ret;
			st->regs_hw[i] = st->regs[i];
			dev_dbg(&st->spi->dev, "[%d] 0x%X\n",
				i, (u32)st->regs[i] | i);
		}
	}
	return 0;
}