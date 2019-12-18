#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  unsigned int u16 ;
struct itcw {int dummy; } ;
struct dcw {int dummy; } ;
struct TYPE_14__ {unsigned int trk_per_cyl; int dev_type; } ;
struct TYPE_18__ {scalar_t__ operation; int nr_cyl; } ;
struct TYPE_17__ {scalar_t__ type; } ;
struct dasd_eckd_private {int real_cyl; TYPE_1__ rdc_data; TYPE_5__ attrib; TYPE_4__ uid; TYPE_3__* ned; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;
struct TYPE_19__ {int define_extent; int verify_base; int hyper_pav; int time_stamp; } ;
struct TYPE_15__ {unsigned int record; int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; } ;
struct TYPE_13__ {int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; } ;
struct TYPE_12__ {int check_bytes; int length_valid; int length_scope; int imbedded_ccw_valid; } ;
struct TYPE_22__ {int orientation; int operation; } ;
struct LRE_eckd_data {int extended_operation; int sector; unsigned int length; int imbedded_ccw; int count; TYPE_2__ search_arg; TYPE_11__ seek_addr; TYPE_10__ auxiliary; TYPE_9__ operation; } ;
struct TYPE_21__ {scalar_t__ operation; int mode; } ;
struct TYPE_20__ {int perm; } ;
struct DE_eckd_data {unsigned int blk_size; int ga_extended; int ep_format; unsigned int ep_rec_per_track; TYPE_11__ end_ext; TYPE_11__ beg_ext; TYPE_8__ attributes; TYPE_7__ mask; } ;
struct PFX_eckd_data {int format; TYPE_6__ validity; int /*<<< orphan*/  base_lss; int /*<<< orphan*/  base_address; struct LRE_eckd_data locate_record; struct DE_eckd_data define_extent; } ;
typedef  int /*<<< orphan*/  pfxdata ;
struct TYPE_16__ {int /*<<< orphan*/  ID; int /*<<< orphan*/  unit_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ DASD_BYPASS_CACHE ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_PFX ; 
 int /*<<< orphan*/  DASD_ECKD_CCW_PFX_READ ; 
#define  DASD_ECKD_CCW_READ_COUNT_MT 130 
#define  DASD_ECKD_CCW_READ_TRACK_DATA 129 
#define  DASD_ECKD_CCW_WRITE_TRACK_DATA 128 
 scalar_t__ DASD_SEQ_ACCESS ; 
 scalar_t__ DASD_SEQ_PRESTAGE ; 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int PTR_ERR_OR_ZERO (struct dcw*) ; 
 scalar_t__ UA_BASE_PAV_ALIAS ; 
 scalar_t__ UA_HYPER_PAV_ALIAS ; 
 int ceil_quot (unsigned int,int) ; 
 struct dcw* itcw_add_dcw (struct itcw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct PFX_eckd_data*,int,unsigned int) ; 
 int /*<<< orphan*/  memset (struct PFX_eckd_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ch_t (TYPE_11__*,int,unsigned int) ; 
 int set_timestamp (int /*<<< orphan*/ *,struct DE_eckd_data*,struct dasd_device*) ; 

__attribute__((used)) static int prepare_itcw(struct itcw *itcw,
			unsigned int trk, unsigned int totrk, int cmd,
			struct dasd_device *basedev,
			struct dasd_device *startdev,
			unsigned int rec_on_trk, int count,
			unsigned int blksize,
			unsigned int total_data_size,
			unsigned int tlf,
			unsigned int blk_per_trk)
{
	struct PFX_eckd_data pfxdata;
	struct dasd_eckd_private *basepriv, *startpriv;
	struct DE_eckd_data *dedata;
	struct LRE_eckd_data *lredata;
	struct dcw *dcw;

	u32 begcyl, endcyl;
	u16 heads, beghead, endhead;
	u8 pfx_cmd;

	int rc = 0;
	int sector = 0;
	int dn, d;


	/* setup prefix data */
	basepriv = basedev->private;
	startpriv = startdev->private;
	dedata = &pfxdata.define_extent;
	lredata = &pfxdata.locate_record;

	memset(&pfxdata, 0, sizeof(pfxdata));
	pfxdata.format = 1; /* PFX with LRE */
	pfxdata.base_address = basepriv->ned->unit_addr;
	pfxdata.base_lss = basepriv->ned->ID;
	pfxdata.validity.define_extent = 1;

	/* private uid is kept up to date, conf_data may be outdated */
	if (startpriv->uid.type == UA_BASE_PAV_ALIAS)
		pfxdata.validity.verify_base = 1;

	if (startpriv->uid.type == UA_HYPER_PAV_ALIAS) {
		pfxdata.validity.verify_base = 1;
		pfxdata.validity.hyper_pav = 1;
	}

	switch (cmd) {
	case DASD_ECKD_CCW_READ_TRACK_DATA:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = blksize;
		dedata->ga_extended |= 0x42;
		lredata->operation.orientation = 0x0;
		lredata->operation.operation = 0x0C;
		lredata->auxiliary.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_READ;
		break;
	case DASD_ECKD_CCW_WRITE_TRACK_DATA:
		dedata->mask.perm = 0x02;
		dedata->attributes.operation = basepriv->attrib.operation;
		dedata->blk_size = blksize;
		rc = set_timestamp(NULL, dedata, basedev);
		dedata->ga_extended |= 0x42;
		lredata->operation.orientation = 0x0;
		lredata->operation.operation = 0x3F;
		lredata->extended_operation = 0x23;
		lredata->auxiliary.check_bytes = 0x2;
		/*
		 * If XRC is supported the System Time Stamp is set. The
		 * validity of the time stamp must be reflected in the prefix
		 * data as well.
		 */
		if (dedata->ga_extended & 0x08 && dedata->ga_extended & 0x02)
			pfxdata.validity.time_stamp = 1; /* 'Time Stamp Valid' */
		pfx_cmd = DASD_ECKD_CCW_PFX;
		break;
	case DASD_ECKD_CCW_READ_COUNT_MT:
		dedata->mask.perm = 0x1;
		dedata->attributes.operation = DASD_BYPASS_CACHE;
		dedata->ga_extended |= 0x42;
		dedata->blk_size = blksize;
		lredata->operation.orientation = 0x2;
		lredata->operation.operation = 0x16;
		lredata->auxiliary.check_bytes = 0x01;
		pfx_cmd = DASD_ECKD_CCW_PFX_READ;
		break;
	default:
		DBF_DEV_EVENT(DBF_ERR, basedev,
			      "prepare itcw, unknown opcode 0x%x", cmd);
		BUG();
		break;
	}
	if (rc)
		return rc;

	dedata->attributes.mode = 0x3;	/* ECKD */

	heads = basepriv->rdc_data.trk_per_cyl;
	begcyl = trk / heads;
	beghead = trk % heads;
	endcyl = totrk / heads;
	endhead = totrk % heads;

	/* check for sequential prestage - enhance cylinder range */
	if (dedata->attributes.operation == DASD_SEQ_PRESTAGE ||
	    dedata->attributes.operation == DASD_SEQ_ACCESS) {

		if (endcyl + basepriv->attrib.nr_cyl < basepriv->real_cyl)
			endcyl += basepriv->attrib.nr_cyl;
		else
			endcyl = (basepriv->real_cyl - 1);
	}

	set_ch_t(&dedata->beg_ext, begcyl, beghead);
	set_ch_t(&dedata->end_ext, endcyl, endhead);

	dedata->ep_format = 0x20; /* records per track is valid */
	dedata->ep_rec_per_track = blk_per_trk;

	if (rec_on_trk) {
		switch (basepriv->rdc_data.dev_type) {
		case 0x3390:
			dn = ceil_quot(blksize + 6, 232);
			d = 9 + ceil_quot(blksize + 6 * (dn + 1), 34);
			sector = (49 + (rec_on_trk - 1) * (10 + d)) / 8;
			break;
		case 0x3380:
			d = 7 + ceil_quot(blksize + 12, 32);
			sector = (39 + (rec_on_trk - 1) * (8 + d)) / 7;
			break;
		}
	}

	if (cmd == DASD_ECKD_CCW_READ_COUNT_MT) {
		lredata->auxiliary.length_valid = 0;
		lredata->auxiliary.length_scope = 0;
		lredata->sector = 0xff;
	} else {
		lredata->auxiliary.length_valid = 1;
		lredata->auxiliary.length_scope = 1;
		lredata->sector = sector;
	}
	lredata->auxiliary.imbedded_ccw_valid = 1;
	lredata->length = tlf;
	lredata->imbedded_ccw = cmd;
	lredata->count = count;
	set_ch_t(&lredata->seek_addr, begcyl, beghead);
	lredata->search_arg.cyl = lredata->seek_addr.cyl;
	lredata->search_arg.head = lredata->seek_addr.head;
	lredata->search_arg.record = rec_on_trk;

	dcw = itcw_add_dcw(itcw, pfx_cmd, 0,
		     &pfxdata, sizeof(pfxdata), total_data_size);
	return PTR_ERR_OR_ZERO(dcw);
}