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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct kempld_wdt_stage {unsigned int mask; int /*<<< orphan*/  id; } ;
struct kempld_wdt_data {struct kempld_device_data* pld; } ;
struct kempld_device_data {int /*<<< orphan*/  pld_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEMPLD_WDT_STAGE_CFG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KEMPLD_WDT_STAGE_TIMEOUT (int /*<<< orphan*/ ) ; 
 size_t STAGE_CFG_GET_PRESCALER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 unsigned int do_div (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int* kempld_prescaler ; 
 unsigned int kempld_read32 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kempld_read8 (struct kempld_device_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int kempld_wdt_get_timeout(struct kempld_wdt_data *wdt_data,
						struct kempld_wdt_stage *stage)
{
	struct kempld_device_data *pld = wdt_data->pld;
	unsigned int timeout;
	u64 stage_timeout;
	u32 prescaler;
	u32 remainder;
	u8 stage_cfg;

	if (!stage->mask)
		return 0;

	stage_cfg = kempld_read8(pld, KEMPLD_WDT_STAGE_CFG(stage->id));
	stage_timeout = kempld_read32(pld, KEMPLD_WDT_STAGE_TIMEOUT(stage->id));
	prescaler = kempld_prescaler[STAGE_CFG_GET_PRESCALER(stage_cfg)];

	stage_timeout = (stage_timeout & stage->mask) * prescaler;
	remainder = do_div(stage_timeout, pld->pld_clock);
	if (remainder)
		stage_timeout++;

	timeout = stage_timeout;
	WARN_ON_ONCE(timeout != stage_timeout);

	return timeout;
}