#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct board_info {int /*<<< orphan*/  clock_core; int /*<<< orphan*/  espi_nports; int /*<<< orphan*/  chip_mac; int /*<<< orphan*/  clock_mc4; } ;
struct TYPE_5__ {int /*<<< orphan*/  sge; int /*<<< orphan*/  tp; } ;
struct TYPE_6__ {TYPE_1__ params; int /*<<< orphan*/  sge; int /*<<< orphan*/  tp; scalar_t__ espi; scalar_t__ regs; } ;
typedef  TYPE_2__ adapter_t ;

/* Variables and functions */
 scalar_t__ A_MC4_CFG ; 
 scalar_t__ A_MC5_CONFIG ; 
 int EIO ; 
 int F_MC4_SLOW ; 
 int F_M_BUS_ENABLE ; 
 int F_READY ; 
 int F_TCAM_RESET ; 
 struct board_info* board_info (TYPE_2__*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ t1_espi_init (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int t1_sge_configure (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ t1_tp_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int t1_init_hw_modules(adapter_t *adapter)
{
	int err = -EIO;
	const struct board_info *bi = board_info(adapter);

	if (!bi->clock_mc4) {
		u32 val = readl(adapter->regs + A_MC4_CFG);

		writel(val | F_READY | F_MC4_SLOW, adapter->regs + A_MC4_CFG);
		writel(F_M_BUS_ENABLE | F_TCAM_RESET,
		       adapter->regs + A_MC5_CONFIG);
	}

	if (adapter->espi && t1_espi_init(adapter->espi, bi->chip_mac,
					  bi->espi_nports))
		goto out_err;

	if (t1_tp_reset(adapter->tp, &adapter->params.tp, bi->clock_core))
		goto out_err;

	err = t1_sge_configure(adapter->sge, &adapter->params.sge);
	if (err)
		goto out_err;

	err = 0;
out_err:
	return err;
}