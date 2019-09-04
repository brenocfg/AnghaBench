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
struct dc_bios {int dummy; } ;
typedef  enum as_signal_type { ____Placeholder_as_signal_type } as_signal_type ;

/* Variables and functions */

__attribute__((used)) static uint32_t bios_parser_get_ss_entry_number(
	struct dc_bios *dcb,
	enum as_signal_type signal)
{
	/* TODO: DAL2 atomfirmware implementation does not need this.
	 * why DAL3 need this?
	 */
	return 1;
}