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
struct w5300_priv {scalar_t__ indirect; } ;

/* Variables and functions */
 int MR_IND ; 
 int MR_PB ; 
 int MR_RST ; 
 int MR_WDF (int) ; 
 int /*<<< orphan*/  W5300_IMR ; 
 int /*<<< orphan*/  W5300_MR ; 
 int /*<<< orphan*/  W5300_MTYPE ; 
 int /*<<< orphan*/  W5300_RMSRH ; 
 int /*<<< orphan*/  W5300_RMSRL ; 
 int /*<<< orphan*/  W5300_TMSRH ; 
 int /*<<< orphan*/  W5300_TMSRL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  w5300_write (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w5300_write32 (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w5300_write_direct (struct w5300_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  w5300_write_macaddr (struct w5300_priv*) ; 

__attribute__((used)) static void w5300_hw_reset(struct w5300_priv *priv)
{
	w5300_write_direct(priv, W5300_MR, MR_RST);
	mdelay(5);
	w5300_write_direct(priv, W5300_MR, priv->indirect ?
				 MR_WDF(7) | MR_PB | MR_IND :
				 MR_WDF(7) | MR_PB);
	w5300_write(priv, W5300_IMR, 0);
	w5300_write_macaddr(priv);

	/* Configure 128K of internal memory
	 * as 64K RX fifo and 64K TX fifo
	 */
	w5300_write32(priv, W5300_RMSRL, 64 << 24);
	w5300_write32(priv, W5300_RMSRH, 0);
	w5300_write32(priv, W5300_TMSRL, 64 << 24);
	w5300_write32(priv, W5300_TMSRH, 0);
	w5300_write(priv, W5300_MTYPE, 0x00ff);
}