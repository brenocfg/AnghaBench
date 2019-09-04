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
struct adv7180_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADV7180_EXTENDED_OUTPUT_CONTROL_NTSCDIS ; 
 int /*<<< orphan*/  ADV7180_NTSC_V_BIT_END_MANUAL_NVEND ; 
 int /*<<< orphan*/  ADV7180_REG_EXTENDED_OUTPUT_CONTROL ; 
 int /*<<< orphan*/  ADV7180_REG_NTSC_V_BIT_END ; 
 int adv7180_write (struct adv7180_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv7180_init(struct adv7180_state *state)
{
	int ret;

	/* ITU-R BT.656-4 compatible */
	ret = adv7180_write(state, ADV7180_REG_EXTENDED_OUTPUT_CONTROL,
			ADV7180_EXTENDED_OUTPUT_CONTROL_NTSCDIS);
	if (ret < 0)
		return ret;

	/* Manually set V bit end position in NTSC mode */
	return adv7180_write(state, ADV7180_REG_NTSC_V_BIT_END,
					ADV7180_NTSC_V_BIT_END_MANUAL_NVEND);
}