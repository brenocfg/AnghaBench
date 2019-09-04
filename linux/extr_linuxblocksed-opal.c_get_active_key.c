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
typedef  int /*<<< orphan*/  uid ;
typedef  int /*<<< orphan*/  u8 ;
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int OPAL_CALL ; 
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 size_t OPAL_GET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int build_locking_range (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_active_key_cont ; 
 int /*<<< orphan*/ ** opalmethod ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_active_key(struct opal_dev *dev, void *data)
{
	u8 uid[OPAL_UID_LENGTH];
	int err = 0;
	u8 *lr = data;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	err = build_locking_range(uid, sizeof(uid), *lr);
	if (err)
		return err;

	err = 0;
	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, uid, OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, opalmethod[OPAL_GET], OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 3); /* startCloumn */
	add_token_u8(&err, dev, 10); /* ActiveKey */
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 4); /* endColumn */
	add_token_u8(&err, dev, 10); /* ActiveKey */
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	if (err) {
		pr_debug("Error building get active key command\n");
		return err;
	}

	return finalize_and_send(dev, get_active_key_cont);
}