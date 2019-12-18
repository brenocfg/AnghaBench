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
 int /*<<< orphan*/  W5100_RMSR ; 
 int /*<<< orphan*/  W5100_TMSR ; 
 int /*<<< orphan*/  w5100_write (struct w5100_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void w5100_memory_configure(struct w5100_priv *priv)
{
	/* Configure 16K of internal memory
	 * as 8K RX buffer and 8K TX buffer
	 */
	w5100_write(priv, W5100_RMSR, 0x03);
	w5100_write(priv, W5100_TMSR, 0x03);
}