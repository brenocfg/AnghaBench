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
typedef  int /*<<< orphan*/  u8 ;
struct opal_key {int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int ERANGE ; 
 size_t OPAL_C_PIN_SID ; 
 int OPAL_UID_LENGTH ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ generic_pw_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct opal_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int set_sid_cpin_pin(struct opal_dev *dev, void *data)
{
	u8 cpin_uid[OPAL_UID_LENGTH];
	struct opal_key *key = data;

	memcpy(cpin_uid, opaluid[OPAL_C_PIN_SID], OPAL_UID_LENGTH);

	if (generic_pw_cmd(key->key, key->key_len, cpin_uid, dev)) {
		pr_debug("Error building Set SID cpin\n");
		return -ERANGE;
	}
	return finalize_and_send(dev, parse_and_check_status);
}