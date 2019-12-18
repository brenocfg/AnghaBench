#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct fmdev {int asci_id; } ;
struct TYPE_3__ {int* buff; } ;
struct TYPE_4__ {TYPE_1__ groupdatabuff; } ;
struct fm_rdsdata_format {TYPE_2__ data; } ;

/* Variables and functions */
 int FM_RX_RDS_INFO_FIELD_MAX ; 
 int /*<<< orphan*/  swap (int,int) ; 

__attribute__((used)) static void fm_rdsparse_swapbytes(struct fmdev *fmdev,
		struct fm_rdsdata_format *rds_format)
{
	u8 index = 0;
	u8 *rds_buff;

	/*
	 * Since in Orca the 2 RDS Data bytes are in little endian and
	 * in Dolphin they are in big endian, the parsing of the RDS data
	 * is chip dependent
	 */
	if (fmdev->asci_id != 0x6350) {
		rds_buff = &rds_format->data.groupdatabuff.buff[0];
		while (index + 1 < FM_RX_RDS_INFO_FIELD_MAX) {
			swap(rds_buff[index], rds_buff[index + 1]);
			index += 2;
		}
	}
}