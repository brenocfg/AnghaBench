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
struct lan9303 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD ; 
 int /*<<< orphan*/  LAN9303_SWITCH_CSR_CMD_BUSY ; 
 int lan9303_read_wait (struct lan9303*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_switch_wait_for_completion(struct lan9303 *chip)
{
	return lan9303_read_wait(chip, LAN9303_SWITCH_CSR_CMD,
				 LAN9303_SWITCH_CSR_CMD_BUSY);
}