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
 scalar_t__ EF4_REV_FALCON_B0 ; 
 scalar_t__ ef4_nic_rev (struct ef4_nic*) ; 

__attribute__((used)) static inline bool ef4_nic_is_dual_func(struct ef4_nic *efx)
{
	return ef4_nic_rev(efx) < EF4_REV_FALCON_B0;
}