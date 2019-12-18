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
struct device {int dummy; } ;
struct nvdimm {int /*<<< orphan*/  dimm_id; struct device dev; } ;
struct key {int /*<<< orphan*/  sem; } ;
struct encrypted_key_payload {scalar_t__ decrypted_datalen; } ;
typedef  int /*<<< orphan*/  NVDIMM_PREFIX ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int /*<<< orphan*/  NVDIMM_KEY_DESC_LEN ; 
 scalar_t__ NVDIMM_PASSPHRASE_LEN ; 
 int /*<<< orphan*/  PTR_ERR (struct key*) ; 
 struct encrypted_key_payload* dereference_key_locked (struct key*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  key_type_encrypted ; 
 struct key* request_key (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct key *nvdimm_request_key(struct nvdimm *nvdimm)
{
	struct key *key = NULL;
	static const char NVDIMM_PREFIX[] = "nvdimm:";
	char desc[NVDIMM_KEY_DESC_LEN + sizeof(NVDIMM_PREFIX)];
	struct device *dev = &nvdimm->dev;

	sprintf(desc, "%s%s", NVDIMM_PREFIX, nvdimm->dimm_id);
	key = request_key(&key_type_encrypted, desc, "");
	if (IS_ERR(key)) {
		if (PTR_ERR(key) == -ENOKEY)
			dev_dbg(dev, "request_key() found no key\n");
		else
			dev_dbg(dev, "request_key() upcall failed\n");
		key = NULL;
	} else {
		struct encrypted_key_payload *epayload;

		down_read(&key->sem);
		epayload = dereference_key_locked(key);
		if (epayload->decrypted_datalen != NVDIMM_PASSPHRASE_LEN) {
			up_read(&key->sem);
			key_put(key);
			key = NULL;
		}
	}

	return key;
}