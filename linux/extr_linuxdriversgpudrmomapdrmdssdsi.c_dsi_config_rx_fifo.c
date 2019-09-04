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
typedef  int u8 ;
typedef  int u32 ;
struct dsi_data {TYPE_1__* vc; } ;
typedef  enum fifo_size { ____Placeholder_fifo_size } fifo_size ;
struct TYPE_2__ {int rx_fifo_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DSI_RX_FIFO_VC_SIZE ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int FLD_VAL (int,int,int) ; 
 int /*<<< orphan*/  dsi_write_reg (struct dsi_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dsi_config_rx_fifo(struct dsi_data *dsi,
		enum fifo_size size1, enum fifo_size size2,
		enum fifo_size size3, enum fifo_size size4)
{
	u32 r = 0;
	int add = 0;
	int i;

	dsi->vc[0].rx_fifo_size = size1;
	dsi->vc[1].rx_fifo_size = size2;
	dsi->vc[2].rx_fifo_size = size3;
	dsi->vc[3].rx_fifo_size = size4;

	for (i = 0; i < 4; i++) {
		u8 v;
		int size = dsi->vc[i].rx_fifo_size;

		if (add + size > 4) {
			DSSERR("Illegal FIFO configuration\n");
			BUG();
			return;
		}

		v = FLD_VAL(add, 2, 0) | FLD_VAL(size, 7, 4);
		r |= v << (8 * i);
		/*DSSDBG("RX FIFO vc %d: size %d, add %d\n", i, size, add); */
		add += size;
	}

	dsi_write_reg(dsi, DSI_RX_FIFO_VC_SIZE, r);
}