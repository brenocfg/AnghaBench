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
struct w5100_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5200_Sn_RXMEM_SIZE (int) ; 
 int /*<<< orphan*/  W5200_Sn_TXMEM_SIZE (int) ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w5200_memory_configure(struct w5100_priv *priv)
{
	int i;

	/* Configure internal RX memory as 16K RX buffer and
	 * internal TX memory as 16K TX buffer
	 */
	w5100_write(priv, W5200_Sn_RXMEM_SIZE(0), 0x10);
	w5100_write(priv, W5200_Sn_TXMEM_SIZE(0), 0x10);

	for (i = 1; i < 8; i++) {
		w5100_write(priv, W5200_Sn_RXMEM_SIZE(i), 0);
		w5100_write(priv, W5200_Sn_TXMEM_SIZE(i), 0);
	}
}