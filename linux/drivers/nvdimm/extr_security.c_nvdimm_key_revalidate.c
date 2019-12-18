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
struct TYPE_4__ {int /*<<< orphan*/  flags; TYPE_1__* ops; } ;
struct nvdimm {TYPE_2__ sec; } ;
struct key {int dummy; } ;
struct TYPE_3__ {int (* change_key ) (struct nvdimm*,void const*,void const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NVDIMM_USER ; 
 void* nvdimm_get_key_payload (struct nvdimm*,struct key**) ; 
 int /*<<< orphan*/  nvdimm_put_key (struct key*) ; 
 int /*<<< orphan*/  nvdimm_security_flags (struct nvdimm*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nvdimm*,void const*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvdimm_key_revalidate(struct nvdimm *nvdimm)
{
	struct key *key;
	int rc;
	const void *data;

	if (!nvdimm->sec.ops->change_key)
		return -EOPNOTSUPP;

	data = nvdimm_get_key_payload(nvdimm, &key);

	/*
	 * Send the same key to the hardware as new and old key to
	 * verify that the key is good.
	 */
	rc = nvdimm->sec.ops->change_key(nvdimm, data, data, NVDIMM_USER);
	if (rc < 0) {
		nvdimm_put_key(key);
		return rc;
	}

	nvdimm_put_key(key);
	nvdimm->sec.flags = nvdimm_security_flags(nvdimm, NVDIMM_USER);
	return 0;
}