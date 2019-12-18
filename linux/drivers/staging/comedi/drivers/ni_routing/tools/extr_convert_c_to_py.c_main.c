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
 int /*<<< orphan*/  device_write (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  family_write (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__* ni_all_route_values ; 
 scalar_t__* ni_device_routes_list ; 

int main(void)
{
	FILE *fp = fopen("ni_values.py", "w");

	/* write route register values */
	fprintf(fp, "ni_route_values = {\n");
	for (int i = 0; ni_all_route_values[i]; ++i)
		family_write(ni_all_route_values[i], fp);
	fprintf(fp, "}\n\n");

	/* write valid device routes */
	fprintf(fp, "ni_device_routes = {\n");
	for (int i = 0; ni_device_routes_list[i]; ++i)
		device_write(ni_device_routes_list[i], fp);
	fprintf(fp, "}\n");

	/* finish; close file */
	fclose(fp);
	return 0;
}