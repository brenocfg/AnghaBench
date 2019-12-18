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
typedef  int u32 ;
struct watchdog_device {int dummy; } ;
struct kempld_wdt_stage {int mask; int id; } ;
struct kempld_wdt_data {struct kempld_wdt_stage* stage; struct kempld_device_data* pld; } ;
struct kempld_device_data {int feature_mask; } ;

/* Variables and functions */
 int ENODEV ; 
 int KEMPLD_FEATURE_BIT_NMI ; 
 int KEMPLD_WDT_STAGE_TIMEOUT (int) ; 
 size_t STAGE_PRETIMEOUT ; 
 size_t STAGE_TIMEOUT ; 
 int /*<<< orphan*/  kempld_get_mutex (struct kempld_device_data*) ; 
 int kempld_read8 (struct kempld_device_data*,int) ; 
 int /*<<< orphan*/  kempld_release_mutex (struct kempld_device_data*) ; 
 int /*<<< orphan*/  kempld_write8 (struct kempld_device_data*,int,int) ; 
 struct kempld_wdt_data* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int kempld_wdt_probe_stages(struct watchdog_device *wdd)
{
	struct kempld_wdt_data *wdt_data = watchdog_get_drvdata(wdd);
	struct kempld_device_data *pld = wdt_data->pld;
	struct kempld_wdt_stage *pretimeout_stage;
	struct kempld_wdt_stage *timeout_stage;
	u8 index, data, data_orig;
	u32 mask;
	int i, j;

	pretimeout_stage = &wdt_data->stage[STAGE_PRETIMEOUT];
	timeout_stage = &wdt_data->stage[STAGE_TIMEOUT];

	pretimeout_stage->mask = 0;
	timeout_stage->mask = 0;

	for (i = 0; i < 3; i++) {
		index = KEMPLD_WDT_STAGE_TIMEOUT(i);
		mask = 0;

		kempld_get_mutex(pld);
		/* Probe each byte individually. */
		for (j = 0; j < 4; j++) {
			data_orig = kempld_read8(pld, index + j);
			kempld_write8(pld, index + j, 0x00);
			data = kempld_read8(pld, index + j);
			/* A failed write means this byte is reserved */
			if (data != 0x00)
				break;
			kempld_write8(pld, index + j, data_orig);
			mask |= 0xff << (j * 8);
		}
		kempld_release_mutex(pld);

		/* Assign available stages to timeout and pretimeout */
		if (!timeout_stage->mask) {
			timeout_stage->mask = mask;
			timeout_stage->id = i;
		} else {
			if (pld->feature_mask & KEMPLD_FEATURE_BIT_NMI) {
				pretimeout_stage->mask = timeout_stage->mask;
				timeout_stage->mask = mask;
				pretimeout_stage->id = timeout_stage->id;
				timeout_stage->id = i;
			}
			break;
		}
	}

	if (!timeout_stage->mask)
		return -ENODEV;

	return 0;
}