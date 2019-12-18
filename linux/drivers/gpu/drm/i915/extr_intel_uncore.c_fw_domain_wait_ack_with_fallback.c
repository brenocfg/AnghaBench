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
struct intel_uncore_forcewake_domain {int /*<<< orphan*/  id; } ;
typedef  enum ack_type { ____Placeholder_ack_type } ack_type ;

/* Variables and functions */
 int const ACK_SET ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,char*,int const,unsigned int) ; 
 int ETIMEDOUT ; 
 int FORCEWAKE_KERNEL ; 
 int /*<<< orphan*/  FORCEWAKE_KERNEL_FALLBACK ; 
 int const fw_ack (struct intel_uncore_forcewake_domain const*) ; 
 int /*<<< orphan*/  fw_clear (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_set (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_domain_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_ack_clear (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_ack_set (struct intel_uncore_forcewake_domain const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fw_domain_wait_ack_with_fallback(const struct intel_uncore_forcewake_domain *d,
				 const enum ack_type type)
{
	const u32 ack_bit = FORCEWAKE_KERNEL;
	const u32 value = type == ACK_SET ? ack_bit : 0;
	unsigned int pass;
	bool ack_detected;

	/*
	 * There is a possibility of driver's wake request colliding
	 * with hardware's own wake requests and that can cause
	 * hardware to not deliver the driver's ack message.
	 *
	 * Use a fallback bit toggle to kick the gpu state machine
	 * in the hope that the original ack will be delivered along with
	 * the fallback ack.
	 *
	 * This workaround is described in HSDES #1604254524 and it's known as:
	 * WaRsForcewakeAddDelayForAck:skl,bxt,kbl,glk,cfl,cnl,icl
	 * although the name is a bit misleading.
	 */

	pass = 1;
	do {
		wait_ack_clear(d, FORCEWAKE_KERNEL_FALLBACK);

		fw_set(d, FORCEWAKE_KERNEL_FALLBACK);
		/* Give gt some time to relax before the polling frenzy */
		udelay(10 * pass);
		wait_ack_set(d, FORCEWAKE_KERNEL_FALLBACK);

		ack_detected = (fw_ack(d) & ack_bit) == value;

		fw_clear(d, FORCEWAKE_KERNEL_FALLBACK);
	} while (!ack_detected && pass++ < 10);

	DRM_DEBUG_DRIVER("%s had to use fallback to %s ack, 0x%x (passes %u)\n",
			 intel_uncore_forcewake_domain_to_str(d->id),
			 type == ACK_SET ? "set" : "clear",
			 fw_ack(d),
			 pass);

	return ack_detected ? 0 : -ETIMEDOUT;
}