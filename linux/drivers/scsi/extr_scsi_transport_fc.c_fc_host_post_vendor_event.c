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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCH_EVT_VENDOR_UNIQUE ; 
 int /*<<< orphan*/  fc_host_post_fc_event (struct Scsi_Host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
fc_host_post_vendor_event(struct Scsi_Host *shost, u32 event_number,
		u32 data_len, char * data_buf, u64 vendor_id)
{
	fc_host_post_fc_event(shost, event_number, FCH_EVT_VENDOR_UNIQUE,
		data_len, data_buf, vendor_id);
}