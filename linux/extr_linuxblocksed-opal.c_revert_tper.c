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
 size_t OPAL_ADMINSP_UID ; 
 int /*<<< orphan*/  OPAL_CALL ; 
 int /*<<< orphan*/  OPAL_ENDLIST ; 
 size_t OPAL_REVERT ; 
 int /*<<< orphan*/  OPAL_STARTLIST ; 
 int /*<<< orphan*/  OPAL_UID_LENGTH ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int finalize_and_send (struct opal_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opalmethod ; 
 int /*<<< orphan*/ * opaluid ; 
 int /*<<< orphan*/  parse_and_check_status ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int revert_tper(struct opal_dev *dev, void *data)
{
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, opaluid[OPAL_ADMINSP_UID],
			     OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, opalmethod[OPAL_REVERT],
			     OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	if (err) {
		pr_debug("Error building REVERT TPER command.\n");
		return err;
	}

	return finalize_and_send(dev, parse_and_check_status);
}