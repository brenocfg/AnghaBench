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
struct macb {int dummy; } ;
typedef  enum macb_bd_control { ____Placeholder_macb_bd_control } macb_bd_control ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BF (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RXBDCTRL ; 
 int /*<<< orphan*/  RXTSMODE ; 
 int /*<<< orphan*/  TXBDCTRL ; 
 int /*<<< orphan*/  TXTSMODE ; 
 int /*<<< orphan*/  gem_writel (struct macb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gem_ptp_set_ts_mode(struct macb *bp,
			       enum macb_bd_control tx_bd_control,
			       enum macb_bd_control rx_bd_control)
{
	gem_writel(bp, TXBDCTRL, GEM_BF(TXTSMODE, tx_bd_control));
	gem_writel(bp, RXBDCTRL, GEM_BF(RXTSMODE, rx_bd_control));

	return 0;
}