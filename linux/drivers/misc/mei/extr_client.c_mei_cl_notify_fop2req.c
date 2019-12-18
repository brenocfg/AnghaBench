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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum mei_cb_file_ops { ____Placeholder_mei_cb_file_ops } mei_cb_file_ops ;

/* Variables and functions */
 int MEI_FOP_NOTIFY_START ; 
 int /*<<< orphan*/  MEI_HBM_NOTIFICATION_START ; 
 int /*<<< orphan*/  MEI_HBM_NOTIFICATION_STOP ; 

u8 mei_cl_notify_fop2req(enum mei_cb_file_ops fop)
{
	if (fop == MEI_FOP_NOTIFY_START)
		return MEI_HBM_NOTIFICATION_START;
	else
		return MEI_HBM_NOTIFICATION_STOP;
}