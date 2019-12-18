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
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ef4_remove_channels (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_filters (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_nic (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_remove_port (struct ef4_nic*) ; 

__attribute__((used)) static void ef4_remove_all(struct ef4_nic *efx)
{
	ef4_remove_channels(efx);
	ef4_remove_filters(efx);
	ef4_remove_port(efx);
	ef4_remove_nic(efx);
}