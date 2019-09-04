#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cmac_statistics {int dummy; } ;
struct cmac {int /*<<< orphan*/  stats; int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRA (int,int,int) ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int /*<<< orphan*/  REG_MODE_CFG (int) ; 
 int /*<<< orphan*/  mac_reset (struct cmac*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_disable(struct cmac *mac, int which)
{
	u32 val;
	int i, port = mac->instance->index;

	/* Reset the port, this also writes the correct WM value */
	mac_reset(mac);

	vsc_read(mac->adapter, REG_MODE_CFG(port), &val);
	if (which & MAC_DIRECTION_RX)
		val &= ~0x2;
	if (which & MAC_DIRECTION_TX)
		val &= ~0x1;
	vsc_write(mac->adapter, REG_MODE_CFG(port), val);
	vsc_read(mac->adapter, REG_MODE_CFG(port), &val);

	/* Clear stats */
	for (i = 0; i <= 0x3a; ++i)
		vsc_write(mac->adapter, CRA(4, port, i), 0);

	/* Clear software counters */
	memset(&mac->stats, 0, sizeof(struct cmac_statistics));

	return 0;
}