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
struct nvdimm {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDD_SECURITY_OVERWRITE ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int nvdimm_in_overwrite(struct nvdimm *nvdimm)
{
	return test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags);
}