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
struct hardware_path {int* bc; scalar_t__ mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static char *print_hwpath(struct hardware_path *path, char *output)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (path->bc[i] == -1)
			continue;
		output += sprintf(output, "%u/", (unsigned char) path->bc[i]);
	}
	output += sprintf(output, "%u", (unsigned char) path->mod);
	return output;
}