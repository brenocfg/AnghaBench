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
struct drm_encoder {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atombios_dig_transmitter_setup2 (struct drm_encoder*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
atombios_dig_transmitter_setup(struct drm_encoder *encoder, int action, uint8_t lane_num, uint8_t lane_set)
{
	atombios_dig_transmitter_setup2(encoder, action, lane_num, lane_set, -1);
}