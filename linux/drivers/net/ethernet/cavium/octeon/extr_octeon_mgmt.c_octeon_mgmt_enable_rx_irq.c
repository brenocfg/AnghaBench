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
struct octeon_mgmt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  octeon_mgmt_set_rx_irq (struct octeon_mgmt*,int) ; 

__attribute__((used)) static void octeon_mgmt_enable_rx_irq(struct octeon_mgmt *p)
{
	octeon_mgmt_set_rx_irq(p, 1);
}