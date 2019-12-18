#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct scsi_data_buffer {TYPE_1__ table; int /*<<< orphan*/  length; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; struct scsi_data_buffer sdb; } ;

/* Variables and functions */
 int DID_ERROR ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,scalar_t__) ; 
 int sg_copy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int fill_from_dev_buffer(struct scsi_cmnd *scp, unsigned char *arr,
				int arr_len)
{
	int act_len;
	struct scsi_data_buffer *sdb = &scp->sdb;

	if (!sdb->length)
		return 0;
	if (scp->sc_data_direction != DMA_FROM_DEVICE)
		return DID_ERROR << 16;

	act_len = sg_copy_from_buffer(sdb->table.sgl, sdb->table.nents,
				      arr, arr_len);
	scsi_set_resid(scp, scsi_bufflen(scp) - act_len);

	return 0;
}