#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum nfp_eth_rate { ____Placeholder_nfp_eth_rate } nfp_eth_rate ;
struct TYPE_3__ {int rate; unsigned int speed; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* nsp_eth_rate_tbl ; 

__attribute__((used)) static unsigned int nfp_eth_rate2speed(enum nfp_eth_rate rate)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(nsp_eth_rate_tbl); i++)
		if (nsp_eth_rate_tbl[i].rate == rate)
			return nsp_eth_rate_tbl[i].speed;

	return 0;
}