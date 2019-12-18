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
struct TYPE_3__ {int first_desc; } ;
struct TYPE_4__ {TYPE_1__ rx_wb_des23; } ;
struct sxgbe_rx_norm_desc {TYPE_2__ rdes23; } ;

/* Variables and functions */

__attribute__((used)) static int sxgbe_get_rx_fd_status(struct sxgbe_rx_norm_desc *p)
{
	return p->rdes23.rx_wb_des23.first_desc;
}