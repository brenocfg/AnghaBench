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
typedef  int u32 ;
struct octeon_device {int priv_flags; } ;

/* Variables and functions */

__attribute__((used)) static inline void lio_set_priv_flag(struct octeon_device *octdev,
				     u32 flag, u32 val)
{
	if (val)
		octdev->priv_flags |= (0x1 << flag);
	else
		octdev->priv_flags &= ~(0x1 << flag);
}