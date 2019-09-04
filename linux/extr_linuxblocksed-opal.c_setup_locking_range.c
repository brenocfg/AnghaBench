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
typedef  int /*<<< orphan*/  uid ;
typedef  scalar_t__ u8 ;
struct TYPE_3__ {scalar_t__ lr; } ;
struct TYPE_4__ {TYPE_1__ opal_key; } ;
struct opal_user_lr_setup {int range_start; int range_length; int /*<<< orphan*/  WLE; int /*<<< orphan*/  RLE; TYPE_2__ session; } ;
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int OPAL_CALL ; 
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 size_t OPAL_SET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int OPAL_UID_LENGTH ; 
 int OPAL_VALUES ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,scalar_t__*,int) ; 
 int /*<<< orphan*/  add_token_u64 (int*,struct opal_dev*,int) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int build_locking_range (scalar_t__*,int,scalar_t__) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int enable_global_lr (struct opal_dev*,scalar_t__*,struct opal_user_lr_setup*) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__** opalmethod ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_locking_range(struct opal_dev *dev, void *data)
{
	u8 uid[OPAL_UID_LENGTH];
	struct opal_user_lr_setup *setup = data;
	u8 lr;
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	lr = setup->session.opal_key.lr;
	err = build_locking_range(uid, sizeof(uid), lr);
	if (err)
		return err;

	if (lr == 0)
		err = enable_global_lr(dev, uid, setup);
	else {
		add_token_u8(&err, dev, OPAL_CALL);
		add_token_bytestring(&err, dev, uid, OPAL_UID_LENGTH);
		add_token_bytestring(&err, dev, opalmethod[OPAL_SET],
				     OPAL_UID_LENGTH);

		add_token_u8(&err, dev, OPAL_STARTLIST);
		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, OPAL_VALUES);
		add_token_u8(&err, dev, OPAL_STARTLIST);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 3); /* Ranges Start */
		add_token_u64(&err, dev, setup->range_start);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 4); /* Ranges length */
		add_token_u64(&err, dev, setup->range_length);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 5); /*ReadLockEnabled */
		add_token_u64(&err, dev, !!setup->RLE);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_STARTNAME);
		add_token_u8(&err, dev, 6); /*WriteLockEnabled*/
		add_token_u64(&err, dev, !!setup->WLE);
		add_token_u8(&err, dev, OPAL_ENDNAME);

		add_token_u8(&err, dev, OPAL_ENDLIST);
		add_token_u8(&err, dev, OPAL_ENDNAME);
		add_token_u8(&err, dev, OPAL_ENDLIST);

	}
	if (err) {
		pr_debug("Error building Setup Locking range command.\n");
		return err;

	}

	return finalize_and_send(dev, parse_and_check_status);
}