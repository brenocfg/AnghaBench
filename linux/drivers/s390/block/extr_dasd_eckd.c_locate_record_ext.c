#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int dev_type; unsigned int trk_per_cyl; } ;
struct dasd_eckd_private {TYPE_2__ rdc_data; } ;
struct dasd_device {struct dasd_eckd_private* private; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_6__ {unsigned int record; int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; } ;
struct TYPE_10__ {int /*<<< orphan*/  head; int /*<<< orphan*/  cyl; } ;
struct TYPE_8__ {int orientation; int operation; } ;
struct TYPE_9__ {int length_valid; } ;
struct LRE_eckd_data {int sector; int count; unsigned int length; int extended_operation; int extended_parameter_length; int* extended_parameter; TYPE_1__ search_arg; TYPE_5__ seek_addr; TYPE_3__ operation; TYPE_4__ auxiliary; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DASD_ECKD_CCW_ERASE 149 
 int /*<<< orphan*/  DASD_ECKD_CCW_LOCATE_RECORD_EXT ; 
#define  DASD_ECKD_CCW_READ 148 
#define  DASD_ECKD_CCW_READ_CKD 147 
#define  DASD_ECKD_CCW_READ_CKD_MT 146 
#define  DASD_ECKD_CCW_READ_COUNT 145 
#define  DASD_ECKD_CCW_READ_HOME_ADDRESS 144 
#define  DASD_ECKD_CCW_READ_KD 143 
#define  DASD_ECKD_CCW_READ_KD_MT 142 
#define  DASD_ECKD_CCW_READ_MT 141 
#define  DASD_ECKD_CCW_READ_RECORD_ZERO 140 
#define  DASD_ECKD_CCW_READ_TRACK 139 
#define  DASD_ECKD_CCW_READ_TRACK_DATA 138 
#define  DASD_ECKD_CCW_WRITE 137 
#define  DASD_ECKD_CCW_WRITE_CKD 136 
#define  DASD_ECKD_CCW_WRITE_CKD_MT 135 
#define  DASD_ECKD_CCW_WRITE_FULL_TRACK 134 
#define  DASD_ECKD_CCW_WRITE_HOME_ADDRESS 133 
#define  DASD_ECKD_CCW_WRITE_KD 132 
#define  DASD_ECKD_CCW_WRITE_KD_MT 131 
#define  DASD_ECKD_CCW_WRITE_MT 130 
#define  DASD_ECKD_CCW_WRITE_RECORD_ZERO 129 
#define  DASD_ECKD_CCW_WRITE_TRACK_DATA 128 
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct dasd_device*,char*,int) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 scalar_t__ __pa (struct LRE_eckd_data*) ; 
 int ceil_quot (unsigned int,int) ; 
 int /*<<< orphan*/  memset (struct LRE_eckd_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_ch_t (TYPE_5__*,unsigned int,unsigned int) ; 

__attribute__((used)) static void locate_record_ext(struct ccw1 *ccw, struct LRE_eckd_data *data,
			      unsigned int trk, unsigned int rec_on_trk,
			      int count, int cmd, struct dasd_device *device,
			      unsigned int reclen, unsigned int tlf)
{
	struct dasd_eckd_private *private = device->private;
	int sector;
	int dn, d;

	if (ccw) {
		ccw->cmd_code = DASD_ECKD_CCW_LOCATE_RECORD_EXT;
		ccw->flags = 0;
		if (cmd == DASD_ECKD_CCW_WRITE_FULL_TRACK)
			ccw->count = 22;
		else
			ccw->count = 20;
		ccw->cda = (__u32)__pa(data);
	}

	memset(data, 0, sizeof(*data));
	sector = 0;
	if (rec_on_trk) {
		switch (private->rdc_data.dev_type) {
		case 0x3390:
			dn = ceil_quot(reclen + 6, 232);
			d = 9 + ceil_quot(reclen + 6 * (dn + 1), 34);
			sector = (49 + (rec_on_trk - 1) * (10 + d)) / 8;
			break;
		case 0x3380:
			d = 7 + ceil_quot(reclen + 12, 32);
			sector = (39 + (rec_on_trk - 1) * (8 + d)) / 7;
			break;
		}
	}
	data->sector = sector;
	/* note: meaning of count depends on the operation
	 *	 for record based I/O it's the number of records, but for
	 *	 track based I/O it's the number of tracks
	 */
	data->count = count;
	switch (cmd) {
	case DASD_ECKD_CCW_WRITE_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x03;
		break;
	case DASD_ECKD_CCW_READ_HOME_ADDRESS:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		break;
	case DASD_ECKD_CCW_WRITE_RECORD_ZERO:
		data->operation.orientation = 0x1;
		data->operation.operation = 0x03;
		data->count++;
		break;
	case DASD_ECKD_CCW_READ_RECORD_ZERO:
		data->operation.orientation = 0x3;
		data->operation.operation = 0x16;
		data->count++;
		break;
	case DASD_ECKD_CCW_WRITE:
	case DASD_ECKD_CCW_WRITE_MT:
	case DASD_ECKD_CCW_WRITE_KD:
	case DASD_ECKD_CCW_WRITE_KD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x01;
		break;
	case DASD_ECKD_CCW_WRITE_CKD:
	case DASD_ECKD_CCW_WRITE_CKD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x03;
		break;
	case DASD_ECKD_CCW_WRITE_FULL_TRACK:
		data->operation.orientation = 0x0;
		data->operation.operation = 0x3F;
		data->extended_operation = 0x11;
		data->length = 0;
		data->extended_parameter_length = 0x02;
		if (data->count > 8) {
			data->extended_parameter[0] = 0xFF;
			data->extended_parameter[1] = 0xFF;
			data->extended_parameter[1] <<= (16 - count);
		} else {
			data->extended_parameter[0] = 0xFF;
			data->extended_parameter[0] <<= (8 - count);
			data->extended_parameter[1] = 0x00;
		}
		data->sector = 0xFF;
		break;
	case DASD_ECKD_CCW_WRITE_TRACK_DATA:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;	/* not tlf, as one might think */
		data->operation.operation = 0x3F;
		data->extended_operation = 0x23;
		break;
	case DASD_ECKD_CCW_READ:
	case DASD_ECKD_CCW_READ_MT:
	case DASD_ECKD_CCW_READ_KD:
	case DASD_ECKD_CCW_READ_KD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x06;
		break;
	case DASD_ECKD_CCW_READ_CKD:
	case DASD_ECKD_CCW_READ_CKD_MT:
		data->auxiliary.length_valid = 0x1;
		data->length = reclen;
		data->operation.operation = 0x16;
		break;
	case DASD_ECKD_CCW_READ_COUNT:
		data->operation.operation = 0x06;
		break;
	case DASD_ECKD_CCW_READ_TRACK:
		data->operation.orientation = 0x1;
		data->operation.operation = 0x0C;
		data->extended_parameter_length = 0;
		data->sector = 0xFF;
		break;
	case DASD_ECKD_CCW_READ_TRACK_DATA:
		data->auxiliary.length_valid = 0x1;
		data->length = tlf;
		data->operation.operation = 0x0C;
		break;
	case DASD_ECKD_CCW_ERASE:
		data->length = reclen;
		data->auxiliary.length_valid = 0x1;
		data->operation.operation = 0x0b;
		break;
	default:
		DBF_DEV_EVENT(DBF_ERR, device,
			    "fill LRE unknown opcode 0x%x", cmd);
		BUG();
	}
	set_ch_t(&data->seek_addr,
		 trk / private->rdc_data.trk_per_cyl,
		 trk % private->rdc_data.trk_per_cyl);
	data->search_arg.cyl = data->seek_addr.cyl;
	data->search_arg.head = data->seek_addr.head;
	data->search_arg.record = rec_on_trk;
}