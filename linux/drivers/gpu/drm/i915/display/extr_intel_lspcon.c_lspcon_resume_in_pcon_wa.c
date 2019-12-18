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
struct intel_lspcon {int dummy; } ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 scalar_t__ intel_digital_port_connected (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 struct intel_dp* lspcon_to_intel_dp (struct intel_lspcon*) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void lspcon_resume_in_pcon_wa(struct intel_lspcon *lspcon)
{
	struct intel_dp *intel_dp = lspcon_to_intel_dp(lspcon);
	struct intel_digital_port *dig_port = dp_to_dig_port(intel_dp);
	unsigned long start = jiffies;

	while (1) {
		if (intel_digital_port_connected(&dig_port->base)) {
			DRM_DEBUG_KMS("LSPCON recovering in PCON mode after %u ms\n",
				      jiffies_to_msecs(jiffies - start));
			return;
		}

		if (time_after(jiffies, start + msecs_to_jiffies(1000)))
			break;

		usleep_range(10000, 15000);
	}

	DRM_DEBUG_KMS("LSPCON DP descriptor mismatch after resume\n");
}