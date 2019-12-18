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
struct ib_smp {scalar_t__ hop_ptr; scalar_t__ hop_cnt; } ;
struct TYPE_2__ {scalar_t__ process_mad; } ;
struct ib_device {TYPE_1__ ops; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 int IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 

__attribute__((used)) static inline enum smi_action smi_check_local_smp(struct ib_smp *smp,
						  struct ib_device *device)
{
	/* C14-9:3 -- We're at the end of the DR segment of path */
	/* C14-9:4 -- Hop Pointer = Hop Count + 1 -> give to SMA/SM */
	return ((device->ops.process_mad &&
		!ib_get_smp_direction(smp) &&
		(smp->hop_ptr == smp->hop_cnt + 1)) ?
		IB_SMI_HANDLE : IB_SMI_DISCARD);
}