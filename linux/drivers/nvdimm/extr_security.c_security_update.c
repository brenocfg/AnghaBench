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
struct TYPE_4__ {void* flags; void* ext_flags; TYPE_1__* ops; } ;
struct device {int dummy; } ;
struct nvdimm {TYPE_2__ sec; struct device dev; } ;
struct key {int dummy; } ;
typedef  enum nvdimm_passphrase_type { ____Placeholder_nvdimm_passphrase_type } nvdimm_passphrase_type ;
struct TYPE_3__ {int (* change_key ) (struct nvdimm*,void const*,void const*,int) ;} ;

/* Variables and functions */
 int ENOKEY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NVDIMM_BASE_KEY ; 
 int NVDIMM_MASTER ; 
 int /*<<< orphan*/  NVDIMM_NEW_KEY ; 
 int NVDIMM_USER ; 
 int check_security_state (struct nvdimm*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  key_serial (struct key*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 void* nvdimm_get_user_key_payload (struct nvdimm*,unsigned int,int /*<<< orphan*/ ,struct key**) ; 
 int /*<<< orphan*/  nvdimm_put_key (struct key*) ; 
 void* nvdimm_security_flags (struct nvdimm*,int) ; 
 int stub1 (struct nvdimm*,void const*,void const*,int) ; 
 struct nvdimm_bus* walk_to_nvdimm_bus (struct device*) ; 

__attribute__((used)) static int security_update(struct nvdimm *nvdimm, unsigned int keyid,
		unsigned int new_keyid,
		enum nvdimm_passphrase_type pass_type)
{
	struct device *dev = &nvdimm->dev;
	struct nvdimm_bus *nvdimm_bus = walk_to_nvdimm_bus(dev);
	struct key *key, *newkey;
	int rc;
	const void *data, *newdata;

	/* The bus lock should be held at the top level of the call stack */
	lockdep_assert_held(&nvdimm_bus->reconfig_mutex);

	if (!nvdimm->sec.ops || !nvdimm->sec.ops->change_key
			|| !nvdimm->sec.flags)
		return -EOPNOTSUPP;

	rc = check_security_state(nvdimm);
	if (rc)
		return rc;

	data = nvdimm_get_user_key_payload(nvdimm, keyid,
			NVDIMM_BASE_KEY, &key);
	if (!data)
		return -ENOKEY;

	newdata = nvdimm_get_user_key_payload(nvdimm, new_keyid,
			NVDIMM_NEW_KEY, &newkey);
	if (!newdata) {
		nvdimm_put_key(key);
		return -ENOKEY;
	}

	rc = nvdimm->sec.ops->change_key(nvdimm, data, newdata, pass_type);
	dev_dbg(dev, "key: %d %d update%s: %s\n",
			key_serial(key), key_serial(newkey),
			pass_type == NVDIMM_MASTER ? "(master)" : "(user)",
			rc == 0 ? "success" : "fail");

	nvdimm_put_key(newkey);
	nvdimm_put_key(key);
	if (pass_type == NVDIMM_MASTER)
		nvdimm->sec.ext_flags = nvdimm_security_flags(nvdimm,
				NVDIMM_MASTER);
	else
		nvdimm->sec.flags = nvdimm_security_flags(nvdimm,
				NVDIMM_USER);
	return rc;
}