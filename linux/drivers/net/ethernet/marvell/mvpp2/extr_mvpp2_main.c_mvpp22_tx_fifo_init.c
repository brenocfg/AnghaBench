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
struct mvpp2 {int dummy; } ;

/* Variables and functions */
 int MVPP22_TX_FIFO_DATA_SIZE_10KB ; 
 int MVPP22_TX_FIFO_DATA_SIZE_3KB ; 
 int /*<<< orphan*/  MVPP22_TX_FIFO_SIZE_REG (int) ; 
 int /*<<< orphan*/  MVPP22_TX_FIFO_THRESH_REG (int) ; 
 int MVPP2_MAX_PORTS ; 
 int MVPP2_TX_FIFO_THRESHOLD_10KB ; 
 int MVPP2_TX_FIFO_THRESHOLD_3KB ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mvpp22_tx_fifo_init(struct mvpp2 *priv)
{
	int port, size, thrs;

	for (port = 0; port < MVPP2_MAX_PORTS; port++) {
		if (port == 0) {
			size = MVPP22_TX_FIFO_DATA_SIZE_10KB;
			thrs = MVPP2_TX_FIFO_THRESHOLD_10KB;
		} else {
			size = MVPP22_TX_FIFO_DATA_SIZE_3KB;
			thrs = MVPP2_TX_FIFO_THRESHOLD_3KB;
		}
		mvpp2_write(priv, MVPP22_TX_FIFO_SIZE_REG(port), size);
		mvpp2_write(priv, MVPP22_TX_FIFO_THRESH_REG(port), thrs);
	}
}