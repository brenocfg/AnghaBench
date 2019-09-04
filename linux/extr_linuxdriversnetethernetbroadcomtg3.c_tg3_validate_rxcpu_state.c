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
struct tg3 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int /*<<< orphan*/  RX_CPU_HWBKPT ; 
 int /*<<< orphan*/  TG3_57766_FW_HANDSHAKE ; 
 scalar_t__ TG3_SBROM_IN_SERVICE_LOOP ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 int tg3_read_indirect_reg32 (struct tg3*,int /*<<< orphan*/ ) ; 
 scalar_t__ tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int tg3_validate_rxcpu_state(struct tg3 *tp)
{
	const int iters = 1000;
	int i;
	u32 val;

	/* Wait for boot code to complete initialization and enter service
	 * loop. It is then safe to download service patches
	 */
	for (i = 0; i < iters; i++) {
		if (tr32(RX_CPU_HWBKPT) == TG3_SBROM_IN_SERVICE_LOOP)
			break;

		udelay(10);
	}

	if (i == iters) {
		netdev_err(tp->dev, "Boot code not ready for service patches\n");
		return -EBUSY;
	}

	val = tg3_read_indirect_reg32(tp, TG3_57766_FW_HANDSHAKE);
	if (val & 0xff) {
		netdev_warn(tp->dev,
			    "Other patches exist. Not downloading EEE patch\n");
		return -EEXIST;
	}

	return 0;
}