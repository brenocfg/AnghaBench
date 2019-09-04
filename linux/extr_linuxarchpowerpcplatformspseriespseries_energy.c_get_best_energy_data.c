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
struct device {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 unsigned long FLAGS_ACTIVATE ; 
 unsigned long FLAGS_MODE2 ; 
 int /*<<< orphan*/  H_BEST_ENERGY ; 
 int H_SUCCESS ; 
 int PLPAR_HCALL9_BUFSIZE ; 
 int /*<<< orphan*/  cpu_to_drc_index (int /*<<< orphan*/ ) ; 
 int plpar_hcall9 (int /*<<< orphan*/ ,unsigned long*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 

__attribute__((used)) static ssize_t get_best_energy_data(struct device *dev,
					char *page, int activate)
{
	int rc;
	unsigned long retbuf[PLPAR_HCALL9_BUFSIZE];
	unsigned long flags = 0;

	flags = FLAGS_MODE2;
	if (activate)
		flags |= FLAGS_ACTIVATE;

	rc = plpar_hcall9(H_BEST_ENERGY, retbuf, flags,
				cpu_to_drc_index(dev->id),
				0, 0, 0, 0, 0, 0, 0);

	if (rc != H_SUCCESS)
		return -EINVAL;

	return sprintf(page, "%lu\n", retbuf[1] >> 32);
}