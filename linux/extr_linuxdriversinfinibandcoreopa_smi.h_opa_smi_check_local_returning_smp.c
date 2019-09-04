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
struct opa_smp {int /*<<< orphan*/  hop_ptr; } ;
struct ib_device {scalar_t__ process_mad; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 int IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 scalar_t__ opa_get_smp_direction (struct opa_smp*) ; 

__attribute__((used)) static inline enum smi_action opa_smi_check_local_returning_smp(struct opa_smp *smp,
								struct ib_device *device)
{
	/* C14-13:3 -- We're at the end of the DR segment of path */
	/* C14-13:4 -- Hop Pointer == 0 -> give to SM */
	return (device->process_mad &&
		opa_get_smp_direction(smp) &&
		!smp->hop_ptr) ? IB_SMI_HANDLE : IB_SMI_DISCARD;
}