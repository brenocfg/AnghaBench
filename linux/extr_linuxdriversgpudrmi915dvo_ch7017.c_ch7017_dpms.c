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
typedef  int u8 ;
struct intel_dvo_device {int dummy; } ;

/* Variables and functions */
 int CH7017_DAC0_POWER_DOWN ; 
 int CH7017_DAC1_POWER_DOWN ; 
 int CH7017_DAC2_POWER_DOWN ; 
 int CH7017_DAC3_POWER_DOWN ; 
 int /*<<< orphan*/  CH7017_LVDS_POWER_DOWN ; 
 int CH7017_LVDS_POWER_DOWN_EN ; 
 int /*<<< orphan*/  CH7017_POWER_MANAGEMENT ; 
 int CH7017_TV_POWER_DOWN_EN ; 
 int /*<<< orphan*/  ch7017_read (struct intel_dvo_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ch7017_write (struct intel_dvo_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ch7017_dpms(struct intel_dvo_device *dvo, bool enable)
{
	u8 val;

	ch7017_read(dvo, CH7017_LVDS_POWER_DOWN, &val);

	/* Turn off TV/VGA, and never turn it on since we don't support it. */
	ch7017_write(dvo, CH7017_POWER_MANAGEMENT,
			CH7017_DAC0_POWER_DOWN |
			CH7017_DAC1_POWER_DOWN |
			CH7017_DAC2_POWER_DOWN |
			CH7017_DAC3_POWER_DOWN |
			CH7017_TV_POWER_DOWN_EN);

	if (enable) {
		/* Turn on the LVDS */
		ch7017_write(dvo, CH7017_LVDS_POWER_DOWN,
			     val & ~CH7017_LVDS_POWER_DOWN_EN);
	} else {
		/* Turn off the LVDS */
		ch7017_write(dvo, CH7017_LVDS_POWER_DOWN,
			     val | CH7017_LVDS_POWER_DOWN_EN);
	}

	/* XXX: Should actually wait for update power status somehow */
	msleep(20);
}