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
struct dmi_header {int type; } ;

/* Variables and functions */
 int /*<<< orphan*/  parse_da_table (struct dmi_header const*) ; 

__attribute__((used)) static void find_cmd_address(const struct dmi_header *dm, void *dummy)
{
	switch (dm->type) {
	case 0xda: /* Calling interface */
		parse_da_table(dm);
		break;
	}
}