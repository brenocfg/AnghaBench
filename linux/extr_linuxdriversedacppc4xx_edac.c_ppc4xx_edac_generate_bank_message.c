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
struct ppc4xx_ecc_status {int dummy; } ;
struct mem_ctl_info {char* dev_name; unsigned int nr_csrows; } ;

/* Variables and functions */
 scalar_t__ ppc4xx_edac_check_bank_error (struct ppc4xx_ecc_status const*,unsigned int) ; 
 int snprintf (char*,size_t,char*,char*,...) ; 

__attribute__((used)) static int
ppc4xx_edac_generate_bank_message(const struct mem_ctl_info *mci,
				  const struct ppc4xx_ecc_status *status,
				  char *buffer,
				  size_t size)
{
	int n, total = 0;
	unsigned int row, rows;

	n = snprintf(buffer, size, "%s: Banks: ", mci->dev_name);

	if (n < 0 || n >= size)
		goto fail;

	buffer += n;
	size -= n;
	total += n;

	for (rows = 0, row = 0; row < mci->nr_csrows; row++) {
		if (ppc4xx_edac_check_bank_error(status, row)) {
			n = snprintf(buffer, size, "%s%u",
					(rows++ ? ", " : ""), row);

			if (n < 0 || n >= size)
				goto fail;

			buffer += n;
			size -= n;
			total += n;
		}
	}

	n = snprintf(buffer, size, "%s; ", rows ? "" : "None");

	if (n < 0 || n >= size)
		goto fail;

	buffer += n;
	size -= n;
	total += n;

 fail:
	return total;
}