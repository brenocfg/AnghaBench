#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ own_bit; } ;
struct TYPE_4__ {TYPE_1__ tx_rd_des23; } ;
struct sxgbe_tx_norm_desc {TYPE_2__ tdes23; } ;

/* Variables and functions */

__attribute__((used)) static void sxgbe_init_tx_desc(struct sxgbe_tx_norm_desc *p)
{
	p->tdes23.tx_rd_des23.own_bit = 0;
}