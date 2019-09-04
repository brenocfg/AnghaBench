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
struct rio_priv {TYPE_1__* inb_atmu_regs; } ;
struct rio_mport {struct rio_priv* priv; } ;
typedef  int dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  riwar; int /*<<< orphan*/  riwtar; } ;

/* Variables and functions */
 int RIO_INB_ATMU_COUNT ; 
 int RIWAR_ENABLE ; 
 int RIWTAR_TRAD_MASK ; 
 int RIWTAR_TRAD_VAL_SHIFT ; 
 int in_be32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 

void fsl_unmap_inb_mem(struct rio_mport *mport, dma_addr_t lstart)
{
	u32 win_start_shift, base_start_shift;
	struct rio_priv *priv = mport->priv;
	u32 riwar, riwtar;
	int i;

	/* skip default window */
	base_start_shift = lstart >> RIWTAR_TRAD_VAL_SHIFT;
	for (i = 0; i < RIO_INB_ATMU_COUNT; i++) {
		riwar = in_be32(&priv->inb_atmu_regs[i].riwar);
		if ((riwar & RIWAR_ENABLE) == 0)
			continue;

		riwtar = in_be32(&priv->inb_atmu_regs[i].riwtar);
		win_start_shift = riwtar & RIWTAR_TRAD_MASK;
		if (win_start_shift == base_start_shift) {
			out_be32(&priv->inb_atmu_regs[i].riwar, riwar & ~RIWAR_ENABLE);
			return;
		}
	}
}