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
struct bnx2x_rx_mode_obj {int /*<<< orphan*/  config_rx_mode; int /*<<< orphan*/  wait_comp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_empty_rx_mode_wait ; 
 int /*<<< orphan*/  bnx2x_set_rx_mode_e1x ; 
 int /*<<< orphan*/  bnx2x_set_rx_mode_e2 ; 
 int /*<<< orphan*/  bnx2x_wait_rx_mode_comp_e2 ; 

void bnx2x_init_rx_mode_obj(struct bnx2x *bp,
			    struct bnx2x_rx_mode_obj *o)
{
	if (CHIP_IS_E1x(bp)) {
		o->wait_comp      = bnx2x_empty_rx_mode_wait;
		o->config_rx_mode = bnx2x_set_rx_mode_e1x;
	} else {
		o->wait_comp      = bnx2x_wait_rx_mode_comp_e2;
		o->config_rx_mode = bnx2x_set_rx_mode_e2;
	}
}