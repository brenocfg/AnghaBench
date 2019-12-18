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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {int* cmnd; } ;
struct opcode_info_t {int num_attached; int flags; int opcode; int sa; int* len_mask; struct opcode_info_t* arrp; } ;

/* Variables and functions */
 int FF_SA ; 
 int F_INV_OP ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INSUFF_RES_ASC ; 
 int /*<<< orphan*/  INSUFF_RES_ASCQ ; 
 int /*<<< orphan*/  SDEB_IN_CDB ; 
 int check_condition_result ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,int*,int) ; 
 int get_unaligned_be16 (int*) ; 
 int get_unaligned_be32 (int*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_sense_invalid_fld (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int* opcode_ind_arr ; 
 struct opcode_info_t* opcode_info_arr ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,int*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,int*) ; 

__attribute__((used)) static int resp_rsup_opcodes(struct scsi_cmnd *scp,
			     struct sdebug_dev_info *devip)
{
	bool rctd;
	u8 reporting_opts, req_opcode, sdeb_i, supp;
	u16 req_sa, u;
	u32 alloc_len, a_len;
	int k, offset, len, errsts, count, bump, na;
	const struct opcode_info_t *oip;
	const struct opcode_info_t *r_oip;
	u8 *arr;
	u8 *cmd = scp->cmnd;

	rctd = !!(cmd[2] & 0x80);
	reporting_opts = cmd[2] & 0x7;
	req_opcode = cmd[3];
	req_sa = get_unaligned_be16(cmd + 4);
	alloc_len = get_unaligned_be32(cmd + 6);
	if (alloc_len < 4 || alloc_len > 0xffff) {
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 6, -1);
		return check_condition_result;
	}
	if (alloc_len > 8192)
		a_len = 8192;
	else
		a_len = alloc_len;
	arr = kzalloc((a_len < 256) ? 320 : a_len + 64, GFP_ATOMIC);
	if (NULL == arr) {
		mk_sense_buffer(scp, ILLEGAL_REQUEST, INSUFF_RES_ASC,
				INSUFF_RES_ASCQ);
		return check_condition_result;
	}
	switch (reporting_opts) {
	case 0:	/* all commands */
		/* count number of commands */
		for (count = 0, oip = opcode_info_arr;
		     oip->num_attached != 0xff; ++oip) {
			if (F_INV_OP & oip->flags)
				continue;
			count += (oip->num_attached + 1);
		}
		bump = rctd ? 20 : 8;
		put_unaligned_be32(count * bump, arr);
		for (offset = 4, oip = opcode_info_arr;
		     oip->num_attached != 0xff && offset < a_len; ++oip) {
			if (F_INV_OP & oip->flags)
				continue;
			na = oip->num_attached;
			arr[offset] = oip->opcode;
			put_unaligned_be16(oip->sa, arr + offset + 2);
			if (rctd)
				arr[offset + 5] |= 0x2;
			if (FF_SA & oip->flags)
				arr[offset + 5] |= 0x1;
			put_unaligned_be16(oip->len_mask[0], arr + offset + 6);
			if (rctd)
				put_unaligned_be16(0xa, arr + offset + 8);
			r_oip = oip;
			for (k = 0, oip = oip->arrp; k < na; ++k, ++oip) {
				if (F_INV_OP & oip->flags)
					continue;
				offset += bump;
				arr[offset] = oip->opcode;
				put_unaligned_be16(oip->sa, arr + offset + 2);
				if (rctd)
					arr[offset + 5] |= 0x2;
				if (FF_SA & oip->flags)
					arr[offset + 5] |= 0x1;
				put_unaligned_be16(oip->len_mask[0],
						   arr + offset + 6);
				if (rctd)
					put_unaligned_be16(0xa,
							   arr + offset + 8);
			}
			oip = r_oip;
			offset += bump;
		}
		break;
	case 1:	/* one command: opcode only */
	case 2:	/* one command: opcode plus service action */
	case 3:	/* one command: if sa==0 then opcode only else opcode+sa */
		sdeb_i = opcode_ind_arr[req_opcode];
		oip = &opcode_info_arr[sdeb_i];
		if (F_INV_OP & oip->flags) {
			supp = 1;
			offset = 4;
		} else {
			if (1 == reporting_opts) {
				if (FF_SA & oip->flags) {
					mk_sense_invalid_fld(scp, SDEB_IN_CDB,
							     2, 2);
					kfree(arr);
					return check_condition_result;
				}
				req_sa = 0;
			} else if (2 == reporting_opts &&
				   0 == (FF_SA & oip->flags)) {
				mk_sense_invalid_fld(scp, SDEB_IN_CDB, 4, -1);
				kfree(arr);	/* point at requested sa */
				return check_condition_result;
			}
			if (0 == (FF_SA & oip->flags) &&
			    req_opcode == oip->opcode)
				supp = 3;
			else if (0 == (FF_SA & oip->flags)) {
				na = oip->num_attached;
				for (k = 0, oip = oip->arrp; k < na;
				     ++k, ++oip) {
					if (req_opcode == oip->opcode)
						break;
				}
				supp = (k >= na) ? 1 : 3;
			} else if (req_sa != oip->sa) {
				na = oip->num_attached;
				for (k = 0, oip = oip->arrp; k < na;
				     ++k, ++oip) {
					if (req_sa == oip->sa)
						break;
				}
				supp = (k >= na) ? 1 : 3;
			} else
				supp = 3;
			if (3 == supp) {
				u = oip->len_mask[0];
				put_unaligned_be16(u, arr + 2);
				arr[4] = oip->opcode;
				for (k = 1; k < u; ++k)
					arr[4 + k] = (k < 16) ?
						 oip->len_mask[k] : 0xff;
				offset = 4 + u;
			} else
				offset = 4;
		}
		arr[1] = (rctd ? 0x80 : 0) | supp;
		if (rctd) {
			put_unaligned_be16(0xa, arr + offset);
			offset += 12;
		}
		break;
	default:
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 2);
		kfree(arr);
		return check_condition_result;
	}
	offset = (offset < a_len) ? offset : a_len;
	len = (offset < alloc_len) ? offset : alloc_len;
	errsts = fill_from_dev_buffer(scp, arr, len);
	kfree(arr);
	return errsts;
}