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
struct TYPE_3__ {unsigned int code; char* text; } ;
typedef  TYPE_1__ twa_message_type ;

/* Variables and functions */

__attribute__((used)) static char *twa_string_lookup(twa_message_type *table, unsigned int code)
{
	int index;

	for (index = 0; ((code != table[index].code) &&
		      (table[index].text != (char *)0)); index++);
	return(table[index].text);
}