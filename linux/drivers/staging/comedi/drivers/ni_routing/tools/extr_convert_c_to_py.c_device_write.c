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
struct ni_device_routes {char* device; TYPE_1__* routes; } ;
struct TYPE_2__ {scalar_t__ dest; scalar_t__* src; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_valid_ni_sig (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

void device_write(const struct ni_device_routes *dR, FILE *fp)
{
	fprintf(fp,
		"  \"%s\" : {\n"
		"    # dest -> [src0, src1, ...]\n"
		, dR->device);

	unsigned int i = 0;

	while (dR->routes[i].dest != 0) {
		if (!is_valid_ni_sig(dR->routes[i].dest)) {
			fprintf(stderr,
				"Invalid NI signal value [%u] for destination %s.[%u]\n",
				dR->routes[i].dest, dR->device, i);
			exit(1);
		}

		fprintf(fp, "    %u : [", dR->routes[i].dest);

		unsigned int j = 0;

		while (dR->routes[i].src[j] != 0) {
			if (!is_valid_ni_sig(dR->routes[i].src[j])) {
				fprintf(stderr,
					"Invalid NI signal value [%u] for source %s.[%u].[%u]\n",
					dR->routes[i].src[j], dR->device, i, j);
				exit(1);
			}

			fprintf(fp, "%u,", dR->routes[i].src[j]);

			++j;
		}
		fprintf(fp, "],\n");

		++i;
	}
	fprintf(fp, "  },\n\n");
}