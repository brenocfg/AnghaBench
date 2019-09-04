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
struct opal_dev {int /*<<< orphan*/  comid; } ;

/* Variables and functions */
 int OPAL_CALL ; 
 int OPAL_ENDLIST ; 
 int OPAL_ENDNAME ; 
 size_t OPAL_SET ; 
 int OPAL_STARTLIST ; 
 int OPAL_STARTNAME ; 
 size_t OPAL_UID_LENGTH ; 
 int OPAL_VALUES ; 
 int /*<<< orphan*/  add_token_bytestring (int*,struct opal_dev*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int) ; 
 int /*<<< orphan*/  clear_opal_cmd (struct opal_dev*) ; 
 int /*<<< orphan*/ ** opalmethod ; 
 int /*<<< orphan*/  set_comid (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int generic_pw_cmd(u8 *key, size_t key_len, u8 *cpin_uid,
			  struct opal_dev *dev)
{
	int err = 0;

	clear_opal_cmd(dev);
	set_comid(dev, dev->comid);

	add_token_u8(&err, dev, OPAL_CALL);
	add_token_bytestring(&err, dev, cpin_uid, OPAL_UID_LENGTH);
	add_token_bytestring(&err, dev, opalmethod[OPAL_SET],
			     OPAL_UID_LENGTH);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, OPAL_VALUES);
	add_token_u8(&err, dev, OPAL_STARTLIST);
	add_token_u8(&err, dev, OPAL_STARTNAME);
	add_token_u8(&err, dev, 3); /* PIN */
	add_token_bytestring(&err, dev, key, key_len);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);
	add_token_u8(&err, dev, OPAL_ENDNAME);
	add_token_u8(&err, dev, OPAL_ENDLIST);

	return err;
}