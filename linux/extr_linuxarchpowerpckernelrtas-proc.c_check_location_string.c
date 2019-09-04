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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_location (struct seq_file*,char const*) ; 
 scalar_t__ isalpha (char const) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 

__attribute__((used)) static void check_location_string(struct seq_file *m, const char *c)
{
	while (*c) {
		if (isalpha(*c) || *c == '.')
			check_location(m, c);
		else if (*c == '/' || *c == '-')
			seq_printf(m, " at ");
		c++;
	}
}