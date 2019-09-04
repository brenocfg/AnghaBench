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
typedef  int u32 ;
struct de_private {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MacMode ; 
 int RxTx ; 
 int /*<<< orphan*/  de_is_running (struct de_private*) ; 
 int dr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void de_stop_rxtx (struct de_private *de)
{
	u32 macmode;
	unsigned int i = 1300/100;

	macmode = dr32(MacMode);
	if (macmode & RxTx) {
		dw32(MacMode, macmode & ~RxTx);
		dr32(MacMode);
	}

	/* wait until in-flight frame completes.
	 * Max time @ 10BT: 1500*8b/10Mbps == 1200us (+ 100us margin)
	 * Typically expect this loop to end in < 50 us on 100BT.
	 */
	while (--i) {
		if (!de_is_running(de))
			return;
		udelay(100);
	}

	netdev_warn(de->dev, "timeout expired, stopping DMA\n");
}