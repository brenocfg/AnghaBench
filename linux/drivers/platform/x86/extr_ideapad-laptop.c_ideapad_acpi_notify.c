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
typedef  int /*<<< orphan*/  u32 ;
struct ideapad_private {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  VPCCMD_R_VPC1 ; 
 int /*<<< orphan*/  VPCCMD_R_VPC2 ; 
 int /*<<< orphan*/  ideapad_backlight_notify_brightness (struct ideapad_private*) ; 
 int /*<<< orphan*/  ideapad_backlight_notify_power (struct ideapad_private*) ; 
 int /*<<< orphan*/  ideapad_check_special_buttons (struct ideapad_private*) ; 
 int /*<<< orphan*/  ideapad_input_novokey (struct ideapad_private*) ; 
 int /*<<< orphan*/  ideapad_input_report (struct ideapad_private*,unsigned long) ; 
 int /*<<< orphan*/  ideapad_sync_rfk_state (struct ideapad_private*) ; 
 int /*<<< orphan*/  ideapad_sync_touchpad_state (struct ideapad_private*) ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long) ; 
 scalar_t__ read_ec_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ test_bit (unsigned long,unsigned long*) ; 

__attribute__((used)) static void ideapad_acpi_notify(acpi_handle handle, u32 event, void *data)
{
	struct ideapad_private *priv = data;
	unsigned long vpc1, vpc2, vpc_bit;

	if (read_ec_data(handle, VPCCMD_R_VPC1, &vpc1))
		return;
	if (read_ec_data(handle, VPCCMD_R_VPC2, &vpc2))
		return;

	vpc1 = (vpc2 << 8) | vpc1;
	for (vpc_bit = 0; vpc_bit < 16; vpc_bit++) {
		if (test_bit(vpc_bit, &vpc1)) {
			switch (vpc_bit) {
			case 9:
				ideapad_sync_rfk_state(priv);
				break;
			case 13:
			case 11:
			case 8:
			case 7:
			case 6:
				ideapad_input_report(priv, vpc_bit);
				break;
			case 5:
				ideapad_sync_touchpad_state(priv);
				break;
			case 4:
				ideapad_backlight_notify_brightness(priv);
				break;
			case 3:
				ideapad_input_novokey(priv);
				break;
			case 2:
				ideapad_backlight_notify_power(priv);
				break;
			case 0:
				ideapad_check_special_buttons(priv);
				break;
			case 1:
				/* Some IdeaPads report event 1 every ~20
				 * seconds while on battery power; some
				 * report this when changing to/from tablet
				 * mode. Squelch this event.
				 */
				break;
			default:
				pr_info("Unknown event: %lu\n", vpc_bit);
			}
		}
	}
}