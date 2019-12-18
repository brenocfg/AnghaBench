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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct gma_encoder {int dummy; } ;

/* Variables and functions */
 int cdv_intel_dp_aux_native_read (struct gma_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool
cdv_intel_dp_aux_native_read_retry(struct gma_encoder *encoder, uint16_t address,
			       uint8_t *recv, int recv_bytes)
{
	int ret, i;

	/*
	 * Sinks are *supposed* to come up within 1ms from an off state,
	 * but we're also supposed to retry 3 times per the spec.
	 */
	for (i = 0; i < 3; i++) {
		ret = cdv_intel_dp_aux_native_read(encoder, address, recv,
					       recv_bytes);
		if (ret == recv_bytes)
			return true;
		udelay(1000);
	}

	return false;
}