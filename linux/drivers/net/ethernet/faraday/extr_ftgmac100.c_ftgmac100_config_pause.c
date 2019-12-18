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
typedef  int /*<<< orphan*/  u32 ;
struct ftgmac100 {scalar_t__ base; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTGMAC100_FCR_FCTHR_EN ; 
 int /*<<< orphan*/  FTGMAC100_FCR_FC_EN ; 
 int /*<<< orphan*/  FTGMAC100_FCR_PAUSE_TIME (int) ; 
 scalar_t__ FTGMAC100_OFFSET_FCR ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ftgmac100_config_pause(struct ftgmac100 *priv)
{
	u32 fcr = FTGMAC100_FCR_PAUSE_TIME(16);

	/* Throttle tx queue when receiving pause frames */
	if (priv->rx_pause)
		fcr |= FTGMAC100_FCR_FC_EN;

	/* Enables sending pause frames when the RX queue is past a
	 * certain threshold.
	 */
	if (priv->tx_pause)
		fcr |= FTGMAC100_FCR_FCTHR_EN;

	iowrite32(fcr, priv->base + FTGMAC100_OFFSET_FCR);
}