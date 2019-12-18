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
typedef  int uint32_t ;
struct bcm_kona_wdt {int base; unsigned int busy_count; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 unsigned int SECWDOG_MAX_TRY ; 
 int SECWDOG_RESERVED_MASK ; 
 int SECWDOG_WD_LOAD_FLAG ; 
 int readl_relaxed (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int secure_register_read(struct bcm_kona_wdt *wdt, uint32_t offset)
{
	uint32_t val;
	unsigned count = 0;

	/*
	 * If the WD_LOAD_FLAG is set, the watchdog counter field is being
	 * updated in hardware. Once the WD timer is updated in hardware, it
	 * gets cleared.
	 */
	do {
		if (unlikely(count > 1))
			udelay(5);
		val = readl_relaxed(wdt->base + offset);
		count++;
	} while ((val & SECWDOG_WD_LOAD_FLAG) && count < SECWDOG_MAX_TRY);

#ifdef CONFIG_BCM_KONA_WDT_DEBUG
	/* Remember the maximum number iterations due to WD_LOAD_FLAG */
	if (count > wdt->busy_count)
		wdt->busy_count = count;
#endif

	/* This is the only place we return a negative value. */
	if (val & SECWDOG_WD_LOAD_FLAG)
		return -ETIMEDOUT;

	/* We always mask out reserved bits. */
	val &= SECWDOG_RESERVED_MASK;

	return val;
}