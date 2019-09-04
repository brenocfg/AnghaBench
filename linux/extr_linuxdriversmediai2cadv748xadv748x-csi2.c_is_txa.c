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
struct adv748x_csi2 {TYPE_1__* state; } ;
struct TYPE_2__ {struct adv748x_csi2 txa; } ;

/* Variables and functions */

__attribute__((used)) static bool is_txa(struct adv748x_csi2 *tx)
{
	return tx == &tx->state->txa;
}