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

/* Variables and functions */
 int /*<<< orphan*/  PDC_LAN_STATION_ID ; 
 int /*<<< orphan*/  PDC_LAN_STATION_ID_READ ; 
 int /*<<< orphan*/  PDC_LAN_STATION_ID_SIZE ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int mem_pdc_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_lock ; 
 int /*<<< orphan*/  pdc_result ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pdc_lan_station_id(char *lan_addr, unsigned long hpa)
{
	int retval;
	unsigned long flags;

	spin_lock_irqsave(&pdc_lock, flags);
	retval = mem_pdc_call(PDC_LAN_STATION_ID, PDC_LAN_STATION_ID_READ,
			__pa(pdc_result), hpa);
	if (retval < 0) {
		/* FIXME: else read MAC from NVRAM */
		memset(lan_addr, 0, PDC_LAN_STATION_ID_SIZE);
	} else {
		memcpy(lan_addr, pdc_result, PDC_LAN_STATION_ID_SIZE);
	}
	spin_unlock_irqrestore(&pdc_lock, flags);

	return retval;
}