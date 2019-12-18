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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_TOUCHPAD_OFF ; 
 int /*<<< orphan*/  KEY_TOUCHPAD_ON ; 
 int /*<<< orphan*/  MSI_STANDARD_EC_FUNCTIONS_ADDRESS ; 
 int MSI_STANDARD_EC_TOUCHPAD_MASK ; 
 int ec_read (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msi_laptop_input_dev ; 
 int /*<<< orphan*/  sparse_keymap_report_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void msi_send_touchpad_key(struct work_struct *ignored)
{
	u8 rdata;
	int result;

	result = ec_read(MSI_STANDARD_EC_FUNCTIONS_ADDRESS, &rdata);
	if (result < 0)
		return;

	sparse_keymap_report_event(msi_laptop_input_dev,
		(rdata & MSI_STANDARD_EC_TOUCHPAD_MASK) ?
		KEY_TOUCHPAD_ON : KEY_TOUCHPAD_OFF, 1, true);
}