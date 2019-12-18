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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_AggSettingRxUpdate (struct adapter*) ; 
 int /*<<< orphan*/  usb_AggSettingTxUpdate (struct adapter*) ; 

__attribute__((used)) static void InitUsbAggregationSetting(struct adapter *Adapter)
{
	/*  Tx aggregation setting */
	usb_AggSettingTxUpdate(Adapter);

	/*  Rx aggregation setting */
	usb_AggSettingRxUpdate(Adapter);
}