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
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int OPAL_CALL ; 
 size_t OPAL_C_PIN_MSID ; 
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 size_t OPAL_GET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 int /*<<< orphan*/  OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_msid_cpin_pin_cont ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_msid_cpin_pin(struct opal_dev *dev, void *data)
{
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, opaluid[OPAL_C_PIN_MSID],
			     OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, opalmethod[OPAL_GET], OPAL_UID_LENGTH);

	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTLIST);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 3); /* Start Column */
	add_token_u8(&err, dev, 3); /* PIN */
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 4); /* End Column */
	add_token_u8(&err, dev, 3); /* Lifecycle Column */
	add_token_u8(&err, dev, OPAL_ENDNAME);

	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDLIST);

	if (err) {
		pr_debug("Error building Get MSID CPIN PIN command.\n");
		return err;
	}

	return finalize_and_send(dev, get_msid_cpin_pin_cont);
}