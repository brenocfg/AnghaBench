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
typedef  int /*<<< orphan*/  u32 ;
struct Scsi_Host {int dummy; } ;
typedef  enum fc_host_event_code { ____Placeholder_fc_host_event_code } fc_host_event_code ;

/* Variables and functions */
 int /*<<< orphan*/  fc_host_post_fc_event (struct Scsi_Host*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
fc_host_post_event(struct Scsi_Host *shost, u32 event_number,
		enum fc_host_event_code event_code, u32 event_data)
{
	fc_host_post_fc_event(shost, event_number, event_code,
		(u32)sizeof(u32), (char *)&event_data, 0);
}