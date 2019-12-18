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
struct mdfld_dsi_pkg_sender {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int wait_for_gen_fifo_empty (struct mdfld_dsi_pkg_sender*,int) ; 

__attribute__((used)) static int wait_for_hs_fifos_empty(struct mdfld_dsi_pkg_sender *sender)
{
	return wait_for_gen_fifo_empty(sender, (BIT(2) | BIT(18)));
}