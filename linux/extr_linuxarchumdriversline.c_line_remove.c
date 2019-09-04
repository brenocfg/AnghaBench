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
struct line {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int setup_one_line (struct line*,int,char*,int /*<<< orphan*/ *,char**) ; 

int line_remove(struct line *lines, unsigned int num, int n, char **error_out)
{
	if (n >= num) {
		*error_out = "Device number out of range";
		return -EINVAL;
	}
	return setup_one_line(lines, n, "none", NULL, error_out);
}