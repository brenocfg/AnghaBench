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
typedef  int /*<<< orphan*/  const u32 ;
struct cdns_i3c_master {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ TX_FIFO ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  writesl (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void cdns_i3c_master_wr_to_tx_fifo(struct cdns_i3c_master *master,
					  const u8 *bytes, int nbytes)
{
	writesl(master->regs + TX_FIFO, bytes, nbytes / 4);
	if (nbytes & 3) {
		u32 tmp = 0;

		memcpy(&tmp, bytes + (nbytes & ~3), nbytes & 3);
		writesl(master->regs + TX_FIFO, &tmp, 1);
	}
}