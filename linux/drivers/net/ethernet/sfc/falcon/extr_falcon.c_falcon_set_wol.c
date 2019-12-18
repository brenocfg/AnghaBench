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
typedef  scalar_t__ u32 ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int falcon_set_wol(struct ef4_nic *efx, u32 type)
{
	if (type != 0)
		return -EINVAL;
	return 0;
}