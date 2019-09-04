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
struct kimage {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  __machine_kexec ; 
 int /*<<< orphan*/  kdump_csum_valid (struct kimage*) ; 
 int /*<<< orphan*/  smp_call_ipl_cpu (int /*<<< orphan*/ ,struct kimage*) ; 
 int /*<<< orphan*/  smp_send_stop () ; 
 int /*<<< orphan*/  tracer_disable () ; 

void machine_kexec(struct kimage *image)
{
	if (image->type == KEXEC_TYPE_CRASH && !kdump_csum_valid(image))
		return;
	tracer_disable();
	smp_send_stop();
	smp_call_ipl_cpu(__machine_kexec, image);
}