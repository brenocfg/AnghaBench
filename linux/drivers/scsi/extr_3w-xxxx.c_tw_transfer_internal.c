#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * srb; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_sg_copy_from_buffer (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static void tw_transfer_internal(TW_Device_Extension *tw_dev, int request_id,
				 void *data, unsigned int len)
{
	scsi_sg_copy_from_buffer(tw_dev->srb[request_id], data, len);
}