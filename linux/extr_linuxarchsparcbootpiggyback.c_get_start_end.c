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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  die (char const*) ; 
 scalar_t__ end_line (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ start_line (char*) ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_start_end(const char *filename, unsigned int *start,
                                               unsigned int *end)
{
	FILE *map;
	char buffer[1024];

	*start = 0;
	*end = 0;
	map = fopen(filename, "r");
	if (!map)
		die(filename);
	while (fgets(buffer, 1024, map)) {
		if (start_line(buffer))
			*start = strtoul(buffer, NULL, 16);
		else if (end_line(buffer))
			*end = strtoul(buffer, NULL, 16);
	}
	fclose (map);

	if (*start == 0 || *end == 0)
		return 0;

	return 1;
}