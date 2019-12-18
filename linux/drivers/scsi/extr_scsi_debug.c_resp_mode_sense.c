#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct sdebug_dev_info {int target; TYPE_3__* sdbg_host; } ;
struct scsi_cmnd {unsigned char* cmnd; TYPE_1__* device; } ;
struct TYPE_6__ {TYPE_2__* shost; } ;
struct TYPE_5__ {int host_no; } ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 unsigned char MODE_SENSE ; 
 int /*<<< orphan*/  SAVING_PARAMS_UNSUP ; 
 int SDEBUG_MAX_MSENSE_SZ ; 
 int /*<<< orphan*/  SDEB_IN_CDB ; 
 scalar_t__ TYPE_DISK ; 
 int check_condition_result ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int get_sdebug_capacity () ; 
 unsigned char get_unaligned_be16 (unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct scsi_cmnd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mk_sense_invalid_fld (struct scsi_cmnd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  put_unaligned_be16 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int,unsigned char*) ; 
 int /*<<< orphan*/  put_unaligned_be64 (int /*<<< orphan*/ ,unsigned char*) ; 
 int resp_caching_pg (unsigned char*,int,int) ; 
 int resp_ctrl_m_pg (unsigned char*,int,int) ; 
 int resp_disconnect_pg (unsigned char*,int,int) ; 
 int resp_err_recov_pg (unsigned char*,int,int) ; 
 int resp_format_pg (unsigned char*,int,int) ; 
 int resp_iec_m_pg (unsigned char*,int,int) ; 
 int resp_sas_pcd_m_spg (unsigned char*,int,int,int) ; 
 int resp_sas_sf_m_pg (unsigned char*,int,int) ; 
 int resp_sas_sha_m_spg (unsigned char*,int) ; 
 int sdebug_capacity ; 
 scalar_t__ sdebug_ptype ; 
 int sdebug_sector_size ; 
 scalar_t__ sdebug_wp ; 

__attribute__((used)) static int resp_mode_sense(struct scsi_cmnd *scp,
			   struct sdebug_dev_info *devip)
{
	int pcontrol, pcode, subpcode, bd_len;
	unsigned char dev_spec;
	int alloc_len, offset, len, target_dev_id;
	int target = scp->device->id;
	unsigned char *ap;
	unsigned char arr[SDEBUG_MAX_MSENSE_SZ];
	unsigned char *cmd = scp->cmnd;
	bool dbd, llbaa, msense_6, is_disk, bad_pcode;

	dbd = !!(cmd[1] & 0x8);		/* disable block descriptors */
	pcontrol = (cmd[2] & 0xc0) >> 6;
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3];
	msense_6 = (MODE_SENSE == cmd[0]);
	llbaa = msense_6 ? false : !!(cmd[1] & 0x10);
	is_disk = (sdebug_ptype == TYPE_DISK);
	if (is_disk && !dbd)
		bd_len = llbaa ? 16 : 8;
	else
		bd_len = 0;
	alloc_len = msense_6 ? cmd[4] : get_unaligned_be16(cmd + 7);
	memset(arr, 0, SDEBUG_MAX_MSENSE_SZ);
	if (0x3 == pcontrol) {  /* Saving values not supported */
		mk_sense_buffer(scp, ILLEGAL_REQUEST, SAVING_PARAMS_UNSUP, 0);
		return check_condition_result;
	}
	target_dev_id = ((devip->sdbg_host->shost->host_no + 1) * 2000) +
			(devip->target * 1000) - 3;
	/* for disks set DPOFUA bit and clear write protect (WP) bit */
	if (is_disk) {
		dev_spec = 0x10;	/* =0x90 if WP=1 implies read-only */
		if (sdebug_wp)
			dev_spec |= 0x80;
	} else
		dev_spec = 0x0;
	if (msense_6) {
		arr[2] = dev_spec;
		arr[3] = bd_len;
		offset = 4;
	} else {
		arr[3] = dev_spec;
		if (16 == bd_len)
			arr[4] = 0x1;	/* set LONGLBA bit */
		arr[7] = bd_len;	/* assume 255 or less */
		offset = 8;
	}
	ap = arr + offset;
	if ((bd_len > 0) && (!sdebug_capacity))
		sdebug_capacity = get_sdebug_capacity();

	if (8 == bd_len) {
		if (sdebug_capacity > 0xfffffffe)
			put_unaligned_be32(0xffffffff, ap + 0);
		else
			put_unaligned_be32(sdebug_capacity, ap + 0);
		put_unaligned_be16(sdebug_sector_size, ap + 6);
		offset += bd_len;
		ap = arr + offset;
	} else if (16 == bd_len) {
		put_unaligned_be64((u64)sdebug_capacity, ap + 0);
		put_unaligned_be32(sdebug_sector_size, ap + 12);
		offset += bd_len;
		ap = arr + offset;
	}

	if ((subpcode > 0x0) && (subpcode < 0xff) && (0x19 != pcode)) {
		/* TODO: Control Extension page */
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
		return check_condition_result;
	}
	bad_pcode = false;

	switch (pcode) {
	case 0x1:	/* Read-Write error recovery page, direct access */
		len = resp_err_recov_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x2:	/* Disconnect-Reconnect page, all devices */
		len = resp_disconnect_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x3:       /* Format device page, direct access */
		if (is_disk) {
			len = resp_format_pg(ap, pcontrol, target);
			offset += len;
		} else
			bad_pcode = true;
		break;
	case 0x8:	/* Caching page, direct access */
		if (is_disk) {
			len = resp_caching_pg(ap, pcontrol, target);
			offset += len;
		} else
			bad_pcode = true;
		break;
	case 0xa:	/* Control Mode page, all devices */
		len = resp_ctrl_m_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x19:	/* if spc==1 then sas phy, control+discover */
		if ((subpcode > 0x2) && (subpcode < 0xff)) {
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
			return check_condition_result;
		}
		len = 0;
		if ((0x0 == subpcode) || (0xff == subpcode))
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
		if ((0x1 == subpcode) || (0xff == subpcode))
			len += resp_sas_pcd_m_spg(ap + len, pcontrol, target,
						  target_dev_id);
		if ((0x2 == subpcode) || (0xff == subpcode))
			len += resp_sas_sha_m_spg(ap + len, pcontrol);
		offset += len;
		break;
	case 0x1c:	/* Informational Exceptions Mode page, all devices */
		len = resp_iec_m_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x3f:	/* Read all Mode pages */
		if ((0 == subpcode) || (0xff == subpcode)) {
			len = resp_err_recov_pg(ap, pcontrol, target);
			len += resp_disconnect_pg(ap + len, pcontrol, target);
			if (is_disk) {
				len += resp_format_pg(ap + len, pcontrol,
						      target);
				len += resp_caching_pg(ap + len, pcontrol,
						       target);
			}
			len += resp_ctrl_m_pg(ap + len, pcontrol, target);
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
			if (0xff == subpcode) {
				len += resp_sas_pcd_m_spg(ap + len, pcontrol,
						  target, target_dev_id);
				len += resp_sas_sha_m_spg(ap + len, pcontrol);
			}
			len += resp_iec_m_pg(ap + len, pcontrol, target);
			offset += len;
		} else {
			mk_sense_invalid_fld(scp, SDEB_IN_CDB, 3, -1);
			return check_condition_result;
		}
		break;
	default:
		bad_pcode = true;
		break;
	}
	if (bad_pcode) {
		mk_sense_invalid_fld(scp, SDEB_IN_CDB, 2, 5);
		return check_condition_result;
	}
	if (msense_6)
		arr[0] = offset - 1;
	else
		put_unaligned_be16((offset - 2), arr + 0);
	return fill_from_dev_buffer(scp, arr, min(alloc_len, offset));
}