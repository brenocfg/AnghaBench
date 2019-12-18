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
struct family_route_values {char* family; } ;
typedef  scalar_t__ register_type ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B (unsigned int) ; 
 scalar_t__ MARKED_I (scalar_t__) ; 
 scalar_t__ MARKED_U (scalar_t__) ; 
 scalar_t__ MARKED_V (scalar_t__) ; 
 unsigned int NI_NAMES_BASE ; 
 unsigned int NI_NUM_NAMES ; 
 scalar_t__ RVij (struct family_route_values const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UNMARK (scalar_t__) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

void family_write(const struct family_route_values *rv, FILE *fp)
{
	fprintf(fp,
		"  \"%s\" : {\n"
		"    # dest -> {src0:val0, src1:val1, ...}\n"
		, rv->family);
	for (unsigned int dest = NI_NAMES_BASE;
	     dest < (NI_NAMES_BASE + NI_NUM_NAMES);
	     ++dest) {
		unsigned int src = NI_NAMES_BASE;

		for (; src < (NI_NAMES_BASE + NI_NUM_NAMES) &&
		     RVij(rv, B(src), B(dest)) == 0; ++src)
			;

		if (src >= (NI_NAMES_BASE + NI_NUM_NAMES))
			continue; /* no data here */

		fprintf(fp, "    %u : {\n", dest);
		for (src = NI_NAMES_BASE; src < (NI_NAMES_BASE + NI_NUM_NAMES);
		     ++src) {
			register_type r = RVij(rv, B(src), B(dest));
			const char *M;

			if (r == 0) {
				continue;
			} else if (MARKED_V(r)) {
				M = "V";
			} else if (MARKED_I(r)) {
				M = "I";
			} else if (MARKED_U(r)) {
				M = "U";
			} else {
				fprintf(stderr,
					"Invalid register marking %s[%u][%u] = %u\n",
					rv->family, dest, src, r);
				exit(1);
			}

			fprintf(fp, "      %u : \"%s(%u)\",\n",
				src, M, UNMARK(r));
		}
		fprintf(fp, "    },\n");
	}
	fprintf(fp, "  },\n\n");
}