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
typedef  int /*<<< orphan*/  u64 ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XMAC_CONFIG ; 
 int /*<<< orphan*/  XMAC_CONFIG_TX_ENABLE ; 
 int /*<<< orphan*/  nr64_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_enable_tx_xmac(struct niu *np, int on)
{
	u64 val = nr64_mac(XMAC_CONFIG);

	if (on)
		val |= XMAC_CONFIG_TX_ENABLE;
	else
		val &= ~XMAC_CONFIG_TX_ENABLE;
	nw64_mac(XMAC_CONFIG, val);
}