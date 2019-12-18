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
struct firedtv {int subunit; int avc_data_length; int /*<<< orphan*/  avc_mutex; scalar_t__ avc_data; } ;
struct avc_response_frame {int* operand; } ;
struct avc_command_frame {int subunit; scalar_t__* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_CTYPE_STATUS ; 
 int /*<<< orphan*/  AVC_OPCODE_VENDOR ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int EN50221_TAG_APP_INFO ; 
 int /*<<< orphan*/  LAST_OPERAND ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_0 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_1 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_2 ; 
 scalar_t__ SFE_VENDOR_OPCODE_CA2HOST ; 
 scalar_t__ SFE_VENDOR_TAG_CA_APPLICATION_INFO ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int /*<<< orphan*/ ) ; 
 int get_ca_object_pos (struct avc_response_frame*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int avc_ca_app_info(struct firedtv *fdtv, unsigned char *app_info,
		    unsigned int *len)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int pos, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->operand[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->operand[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->operand[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->operand[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->operand[4] = 0; /* slot */
	c->operand[5] = SFE_VENDOR_TAG_CA_APPLICATION_INFO; /* ca tag */
	clear_operands(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	/* FIXME: check response code and validate response data */

	pos = get_ca_object_pos(r);
	app_info[0] = (EN50221_TAG_APP_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_APP_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_APP_INFO >>  0) & 0xff;
	app_info[3] = 6 + r->operand[pos + 4];
	app_info[4] = 0x01;
	memcpy(&app_info[5], &r->operand[pos], 5 + r->operand[pos + 4]);
	*len = app_info[3] + 4;
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}