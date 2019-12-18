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
struct timer_list {int dummy; } ;
struct efx_mcdi_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_timer ; 
 int /*<<< orphan*/  efx_mcdi_complete_async (struct efx_mcdi_iface*,int) ; 
 struct efx_mcdi_iface* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct efx_mcdi_iface* mcdi ; 

__attribute__((used)) static void efx_mcdi_timeout_async(struct timer_list *t)
{
	struct efx_mcdi_iface *mcdi = from_timer(mcdi, t, async_timer);

	efx_mcdi_complete_async(mcdi, true);
}