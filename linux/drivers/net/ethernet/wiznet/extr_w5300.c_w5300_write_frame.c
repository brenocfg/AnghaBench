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
typedef  int u16 ;
struct w5300_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5300_S0_TX_FIFO ; 
 int /*<<< orphan*/  W5300_S0_TX_WRSR ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w5300_write32 (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w5300_write_frame(struct w5300_priv *priv, u8 *buf, int len)
{
	u16 fifo;
	int i;

	for (i = 0; i < len; i += 2) {
		fifo  = *buf++ << 8;
		fifo |= *buf++;
		w5300_write(priv, W5300_S0_TX_FIFO, fifo);
	}
	w5300_write32(priv, W5300_S0_TX_WRSR, len);
}