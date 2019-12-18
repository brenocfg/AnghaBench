#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nvdimm_bus {int /*<<< orphan*/  reconfig_mutex; } ;
struct TYPE_4__ {unsigned int overwrite_tmo; void* flags; scalar_t__ overwrite_state; TYPE_1__* ops; } ;
struct nvdimm {TYPE_2__ sec; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  dwork; } ;
struct TYPE_3__ {int (* query_overwrite ) (struct nvdimm*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  NDD_SECURITY_OVERWRITE ; 
 int /*<<< orphan*/  NDD_WORK_PENDING ; 
 int /*<<< orphan*/  NVDIMM_MASTER ; 
 int /*<<< orphan*/  NVDIMM_USER ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 void* nvdimm_security_flags (struct nvdimm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int stub1 (struct nvdimm*) ; 
 int /*<<< orphan*/  sysfs_notify_dirent (scalar_t__) ; 
 int /*<<< orphan*/  system_wq ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (int /*<<< orphan*/ *) ; 

void __nvdimm_security_overwrite_query(struct nvdimm *nvdimm)
{
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(&nvdimm->dev);
	int rc;
	unsigned int tmo;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_assert_held(&nvdimm_bus->reconfig_mutex);

	/*
	 * Abort and release device if we no longer have the overwrite
	 * flag set. It means the work has been canceled.
	 */
	if (!test_bit(NDD_WORK_PENDING, &nvdimm->flags))
		return;

	tmo = nvdimm->sec.overwrite_tmo;

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->query_overwrite
			|| !nvdimm->sec.flags)
		return;

	rc = nvdimm->sec.ops->query_overwrite(nvdimm);
	if (rc == -EBUSY) {

		/* setup delayed work again */
		tmo += 10;
		queue_delayed_work(system_wq, &nvdimm->dwork, tmo * HZ);
		nvdimm->sec.overwrite_tmo = min(15U * 60U, tmo);
		return;
	}

	if (rc < 0)
		dev_dbg(&nvdimm->dev, "overwrite failed\n");
	else
		dev_dbg(&nvdimm->dev, "overwrite completed\n");

	if (nvdimm->sec.overwrite_state)
		sysfs_notify_dirent(nvdimm->sec.overwrite_state);
	nvdimm->sec.overwrite_tmo = 0;
	clear_bit(NDD_SECURITY_OVERWRITE, &nvdimm->flags);
	clear_bit(NDD_WORK_PENDING, &nvdimm->flags);
	put_device(&nvdimm->dev);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_MASTER);
}