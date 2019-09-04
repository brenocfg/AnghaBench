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
struct adf_cfg_section {int dummy; } ;
struct adf_cfg_key_val {int /*<<< orphan*/  val; } ;
struct adf_accel_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_CFG_MAX_VAL_LEN_IN_BYTES ; 
 struct adf_cfg_key_val* adf_cfg_key_value_find (struct adf_cfg_section*,char const*) ; 
 struct adf_cfg_section* adf_cfg_sec_find (struct adf_accel_dev*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adf_cfg_key_val_get(struct adf_accel_dev *accel_dev,
			       const char *sec_name,
			       const char *key_name,
			       char *val)
{
	struct adf_cfg_section *sec = adf_cfg_sec_find(accel_dev, sec_name);
	struct adf_cfg_key_val *keyval = NULL;

	if (sec)
		keyval = adf_cfg_key_value_find(sec, key_name);
	if (keyval) {
		memcpy(val, keyval->val, ADF_CFG_MAX_VAL_LEN_IN_BYTES);
		return 0;
	}
	return -1;
}