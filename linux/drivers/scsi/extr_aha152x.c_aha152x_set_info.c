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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {scalar_t__* time; scalar_t__* count_trans; scalar_t__* count; scalar_t__ busfree_with_check_condition; scalar_t__ busfree_without_done_command; scalar_t__ busfree_without_new_command; scalar_t__ busfree_without_old_command; scalar_t__ busfree_without_any_action; scalar_t__ disconnections; scalar_t__ total_commands; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* HOSTDATA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int idle ; 
 int maxstate ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int aha152x_set_info(struct Scsi_Host *shpnt, char *buffer, int length)
{
	if(!shpnt || !buffer || length<8 || strncmp("aha152x ", buffer, 8)!=0)
		return -EINVAL;

#if defined(AHA152X_STAT)
	if(length>13 && strncmp("reset", buffer+8, 5)==0) {
		int i;

		HOSTDATA(shpnt)->total_commands=0;
		HOSTDATA(shpnt)->disconnections=0;
		HOSTDATA(shpnt)->busfree_without_any_action=0;
		HOSTDATA(shpnt)->busfree_without_old_command=0;
		HOSTDATA(shpnt)->busfree_without_new_command=0;
		HOSTDATA(shpnt)->busfree_without_done_command=0;
		HOSTDATA(shpnt)->busfree_with_check_condition=0;
		for (i = idle; i<maxstate; i++) {
			HOSTDATA(shpnt)->count[i]=0;
			HOSTDATA(shpnt)->count_trans[i]=0;
			HOSTDATA(shpnt)->time[i]=0;
		}

		shost_printk(KERN_INFO, shpnt, "aha152x: stats reset.\n");

	} else
#endif
	{
		return -EINVAL;
	}


	return length;
}