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
struct firedtv {int subunit; int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/  device; int /*<<< orphan*/  avc_data_length; scalar_t__ avc_data; } ;
struct avc_response_frame {int response; } ;
struct avc_command_frame {int subunit; int* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  AVC_CTYPE_CONTROL ; 
 int AVC_DEBUG_APPLICATION_PMT ; 
 int /*<<< orphan*/  AVC_OPCODE_VENDOR ; 
 int AVC_RESPONSE_ACCEPTED ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int EACCES ; 
 int EINVAL ; 
 char EN50221_LIST_MANAGEMENT_ONLY ; 
 int SFE_VENDOR_DE_COMPANYID_0 ; 
 int SFE_VENDOR_DE_COMPANYID_1 ; 
 int SFE_VENDOR_DE_COMPANYID_2 ; 
 int SFE_VENDOR_OPCODE_HOST2CA ; 
 int SFE_VENDOR_TAG_CA_PMT ; 
 int avc_debug ; 
 int avc_write (struct firedtv*) ; 
 int crc32_be (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  debug_pmt (char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pad_operands (struct avc_command_frame*,int) ; 
 scalar_t__ unlikely (int) ; 

int avc_ca_pmt(struct firedtv *fdtv, char *msg, int length)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int list_management;
	int program_info_length;
	int pmt_cmd_id;
	int read_pos;
	int write_pos;
	int es_info_length;
	int crc32_csum;
	int ret;

	if (unlikely(avc_debug & AVC_DEBUG_APPLICATION_PMT))
		debug_pmt(msg, length);

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	if (msg[0] != EN50221_LIST_MANAGEMENT_ONLY) {
		dev_info(fdtv->device, "forcing list_management to ONLY\n");
		msg[0] = EN50221_LIST_MANAGEMENT_ONLY;
	}
	/* We take the cmd_id from the programme level only! */
	list_management = msg[0];
	program_info_length = ((msg[4] & 0x0f) << 8) + msg[5];
	if (program_info_length > 0)
		program_info_length--; /* Remove pmt_cmd_id */
	pmt_cmd_id = msg[6];

	c->operand[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->operand[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->operand[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->operand[3] = SFE_VENDOR_OPCODE_HOST2CA;
	c->operand[4] = 0; /* slot */
	c->operand[5] = SFE_VENDOR_TAG_CA_PMT; /* ca tag */
	c->operand[6] = 0; /* more/last */
	/* Use three bytes for length field in case length > 127 */
	c->operand[10] = list_management;
	c->operand[11] = 0x01; /* pmt_cmd=OK_descramble */

	/* TS program map table */

	c->operand[12] = 0x02; /* Table id=2 */
	c->operand[13] = 0x80; /* Section syntax + length */

	c->operand[15] = msg[1]; /* Program number */
	c->operand[16] = msg[2];
	c->operand[17] = msg[3]; /* Version number and current/next */
	c->operand[18] = 0x00; /* Section number=0 */
	c->operand[19] = 0x00; /* Last section number=0 */
	c->operand[20] = 0x1f; /* PCR_PID=1FFF */
	c->operand[21] = 0xff;
	c->operand[22] = (program_info_length >> 8); /* Program info length */
	c->operand[23] = (program_info_length & 0xff);

	/* CA descriptors at programme level */
	read_pos = 6;
	write_pos = 24;
	if (program_info_length > 0) {
		pmt_cmd_id = msg[read_pos++];
		if (pmt_cmd_id != 1 && pmt_cmd_id != 4)
			dev_err(fdtv->device,
				"invalid pmt_cmd_id %d\n", pmt_cmd_id);
		if (program_info_length > sizeof(c->operand) - 4 - write_pos) {
			ret = -EINVAL;
			goto out;
		}

		memcpy(&c->operand[write_pos], &msg[read_pos],
		       program_info_length);
		read_pos += program_info_length;
		write_pos += program_info_length;
	}
	while (read_pos < length) {
		c->operand[write_pos++] = msg[read_pos++];
		c->operand[write_pos++] = msg[read_pos++];
		c->operand[write_pos++] = msg[read_pos++];
		es_info_length =
			((msg[read_pos] & 0x0f) << 8) + msg[read_pos + 1];
		read_pos += 2;
		if (es_info_length > 0)
			es_info_length--; /* Remove pmt_cmd_id */
		c->operand[write_pos++] = es_info_length >> 8;
		c->operand[write_pos++] = es_info_length & 0xff;
		if (es_info_length > 0) {
			pmt_cmd_id = msg[read_pos++];
			if (pmt_cmd_id != 1 && pmt_cmd_id != 4)
				dev_err(fdtv->device, "invalid pmt_cmd_id %d at stream level\n",
					pmt_cmd_id);

			if (es_info_length > sizeof(c->operand) - 4 -
					     write_pos) {
				ret = -EINVAL;
				goto out;
			}

			memcpy(&c->operand[write_pos], &msg[read_pos],
			       es_info_length);
			read_pos += es_info_length;
			write_pos += es_info_length;
		}
	}
	write_pos += 4; /* CRC */

	c->operand[7] = 0x82;
	c->operand[8] = (write_pos - 10) >> 8;
	c->operand[9] = (write_pos - 10) & 0xff;
	c->operand[14] = write_pos - 15;

	crc32_csum = crc32_be(0, &c->operand[10], c->operand[12] - 1);
	c->operand[write_pos - 4] = (crc32_csum >> 24) & 0xff;
	c->operand[write_pos - 3] = (crc32_csum >> 16) & 0xff;
	c->operand[write_pos - 2] = (crc32_csum >>  8) & 0xff;
	c->operand[write_pos - 1] = (crc32_csum >>  0) & 0xff;
	pad_operands(c, write_pos);

	fdtv->avc_data_length = ALIGN(3 + write_pos, 4);
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	if (r->response != AVC_RESPONSE_ACCEPTED) {
		dev_err(fdtv->device,
			"CA PMT failed with response 0x%x\n", r->response);
		ret = -EACCES;
	}
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}