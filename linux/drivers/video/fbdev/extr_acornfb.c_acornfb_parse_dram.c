#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int dram_size; } ;

/* Variables and functions */
 TYPE_1__ current_par ; 
 unsigned int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void acornfb_parse_dram(char *opt)
{
	unsigned int size;

	size = simple_strtoul(opt, &opt, 0);

	if (opt) {
		switch (*opt) {
		case 'M':
		case 'm':
			size *= 1024;
			/* Fall through */
		case 'K':
		case 'k':
			size *= 1024;
		default:
			break;
		}
	}

	current_par.dram_size = size;
}