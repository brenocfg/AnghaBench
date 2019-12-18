#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ mask; scalar_t__ value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ahc_reg_parse_entry_t ;

/* Variables and functions */
 int printk (char*,...) ; 

int
ahc_print_register(const ahc_reg_parse_entry_t *table, u_int num_entries,
		   const char *name, u_int address, u_int value,
		   u_int *cur_column, u_int wrap_point)
{
	int	printed;
	u_int	printed_mask;

	if (cur_column != NULL && *cur_column >= wrap_point) {
		printk("\n");
		*cur_column = 0;
	}
	printed  = printk("%s[0x%x]", name, value);
	if (table == NULL) {
		printed += printk(" ");
		*cur_column += printed;
		return (printed);
	}
	printed_mask = 0;
	while (printed_mask != 0xFF) {
		int entry;

		for (entry = 0; entry < num_entries; entry++) {
			if (((value & table[entry].mask)
			  != table[entry].value)
			 || ((printed_mask & table[entry].mask)
			  == table[entry].mask))
				continue;

			printed += printk("%s%s",
					  printed_mask == 0 ? ":(" : "|",
					  table[entry].name);
			printed_mask |= table[entry].mask;
			
			break;
		}
		if (entry >= num_entries)
			break;
	}
	if (printed_mask != 0)
		printed += printk(") ");
	else
		printed += printk(" ");
	if (cur_column != NULL)
		*cur_column += printed;
	return (printed);
}