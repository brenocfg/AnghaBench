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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct device {int dummy; } ;
struct nvdimm {int /*<<< orphan*/  flags; TYPE_1__ sec; struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  NDD_SECURITY_OVERWRITE ; 
 int /*<<< orphan*/  NVDIMM_SECURITY_FROZEN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int check_security_state(struct nvdimm *nvdimm)
{
	struct device *dev = &nvdimm->dev;

	if (test_bit(NVDIMM_SECURITY_FROZEN, &nvdimm->sec.flags)) {
		dev_dbg(dev, "Incorrect security state: %#lx\n",
				nvdimm->sec.flags);
		return -EIO;
	}

	if (test_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags)) {
		dev_dbg(dev, "Security operation in progress.\n");
		return -EBUSY;
	}

	return 0;
}