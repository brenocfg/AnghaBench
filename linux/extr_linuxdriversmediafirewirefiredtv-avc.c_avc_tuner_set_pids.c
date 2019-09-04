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
typedef  int u16 ;
struct firedtv {int subunit; int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/  avc_data_length; scalar_t__ avc_data; } ;
struct avc_command_frame {int subunit; int* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  AVC_CTYPE_CONTROL ; 
 int /*<<< orphan*/  AVC_OPCODE_DSD ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int EINVAL ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad_operands (struct avc_command_frame*,int) ; 

int avc_tuner_set_pids(struct firedtv *fdtv, unsigned char pidc, u16 pid[])
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	int ret, pos, k;

	if (pidc > 16 && pidc != 0xff)
		return -EINVAL;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSD;

	c->operand[0] = 0;	/* source plug */
	c->operand[1] = 0xd2;	/* subfunction replace */
	c->operand[2] = 0x20;	/* system id = DVB */
	c->operand[3] = 0x00;	/* antenna number */
	c->operand[4] = 0x00;	/* system_specific_multiplex selection_length */
	c->operand[5] = pidc;	/* Nr_of_dsd_sel_specs */

	pos = 6;
	if (pidc != 0xff)
		for (k = 0; k < pidc; k++) {
			c->operand[pos++] = 0x13; /* flowfunction relay */
			c->operand[pos++] = 0x80; /* dsd_sel_spec_valid_flags -> PID */
			c->operand[pos++] = (pid[k] >> 8) & 0x1f;
			c->operand[pos++] = pid[k] & 0xff;
			c->operand[pos++] = 0x00; /* tableID */
			c->operand[pos++] = 0x00; /* filter_length */
		}
	pad_operands(c, pos);

	fdtv->avc_data_length = ALIGN(3 + pos, 4);
	ret = avc_write(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	if (ret == 0)
		msleep(50);

	return ret;
}