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
typedef  scalar_t__ u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  CEC_ERROR_INJ_MODE_ALWAYS 130 
#define  CEC_ERROR_INJ_MODE_ONCE 129 
#define  CEC_ERROR_INJ_MODE_TOGGLE 128 
 scalar_t__ CEC_ERROR_INJ_OP_ANY ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,scalar_t__) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void cec_pin_show_cmd(struct seq_file *sf, u32 cmd, u8 mode)
{
	if (cmd == CEC_ERROR_INJ_OP_ANY)
		seq_puts(sf, "any,");
	else
		seq_printf(sf, "0x%02x,", cmd);
	switch (mode) {
	case CEC_ERROR_INJ_MODE_ONCE:
		seq_puts(sf, "once ");
		break;
	case CEC_ERROR_INJ_MODE_ALWAYS:
		seq_puts(sf, "always ");
		break;
	case CEC_ERROR_INJ_MODE_TOGGLE:
		seq_puts(sf, "toggle ");
		break;
	default:
		seq_puts(sf, "off ");
		break;
	}
}