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
typedef  int u64 ;
typedef  int u32 ;
struct mv643xx_eth_private {int t_clk; TYPE_1__* shared; } ;
struct TYPE_2__ {scalar_t__ extended_rx_coal_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDMA_CONFIG ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int rdlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrlp (struct mv643xx_eth_private*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_rx_coal(struct mv643xx_eth_private *mp, unsigned int usec)
{
	u64 temp;
	u32 val;

	temp = (u64)usec * mp->t_clk;
	temp += 31999999;
	do_div(temp, 64000000);

	val = rdlp(mp, SDMA_CONFIG);
	if (mp->shared->extended_rx_coal_limit) {
		if (temp > 0xffff)
			temp = 0xffff;
		val &= ~0x023fff80;
		val |= (temp & 0x8000) << 10;
		val |= (temp & 0x7fff) << 7;
	} else {
		if (temp > 0x3fff)
			temp = 0x3fff;
		val &= ~0x003fff00;
		val |= (temp & 0x3fff) << 8;
	}
	wrlp(mp, SDMA_CONFIG, val);
}