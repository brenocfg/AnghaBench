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
struct firedtv {int subunit; int avc_data_length; int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/  device; scalar_t__ avc_data; } ;
struct avc_response_frame {scalar_t__ response; int* operand; } ;
struct avc_command_frame {int subunit; int* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_CTYPE_CONTROL ; 
 int /*<<< orphan*/  AVC_OPCODE_READ_DESCRIPTOR ; 
 scalar_t__ AVC_RESPONSE_ACCEPTED ; 
 scalar_t__ AVC_RESPONSE_STABLE ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int DESCRIPTOR_SUBUNIT_IDENTIFIER ; 
 int EINVAL ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int avc_identify_subunit(struct firedtv *fdtv)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_READ_DESCRIPTOR;

	c->operand[0] = DESCRIPTOR_SUBUNIT_IDENTIFIER;
	c->operand[1] = 0xff;
	c->operand[2] = 0x00;
	c->operand[3] = 0x00; /* length highbyte */
	c->operand[4] = 0x08; /* length lowbyte  */
	c->operand[5] = 0x00; /* offset highbyte */
	c->operand[6] = 0x0d; /* offset lowbyte  */
	clear_operands(c, 7, 8); /* padding */

	fdtv->avc_data_length = 12;
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	if ((r->response != AVC_RESPONSE_STABLE &&
	     r->response != AVC_RESPONSE_ACCEPTED) ||
	    (r->operand[3] << 8) + r->operand[4] != 8) {
		dev_err(fdtv->device, "cannot read subunit identifier\n");
		ret = -EINVAL;
	}
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}