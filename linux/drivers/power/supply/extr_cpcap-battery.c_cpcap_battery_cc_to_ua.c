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
struct cpcap_battery_ddata {int dummy; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS ; 
 int cpcap_battery_cc_raw_div (struct cpcap_battery_ddata*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cpcap_battery_cc_to_ua(struct cpcap_battery_ddata *ddata,
				  s32 sample, s32 accumulator,
				  s16 offset)
{
	return cpcap_battery_cc_raw_div(ddata, sample,
					accumulator, offset,
					sample *
					CPCAP_BATTERY_CC_SAMPLE_PERIOD_MS);
}