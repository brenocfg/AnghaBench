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

__attribute__((used)) static unsigned int get_rx_coal(struct mv643xx_eth_private *mp)
{
	u32 val = rdlp(mp, SDMA_CONFIG);
	u64 temp;

	if (mp->shared->extended_rx_coal_limit)
		temp = ((val & 0x02000000) >> 10) | ((val & 0x003fff80) >> 7);
	else
		temp = (val & 0x003fff00) >> 8;

	temp *= 64000000;
	temp += mp->t_clk / 2;
	do_div(temp, mp->t_clk);

	return (unsigned int)temp;
}