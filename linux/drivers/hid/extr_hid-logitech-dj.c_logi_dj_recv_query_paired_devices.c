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
struct dj_report {int device_index; int /*<<< orphan*/  report_type; int /*<<< orphan*/  report_id; } ;
struct dj_receiver_dev {scalar_t__ type; int /*<<< orphan*/  last_query; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  REPORT_ID_DJ_SHORT ; 
 int /*<<< orphan*/  REPORT_TYPE_CMD_GET_PAIRED_DEVICES ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct dj_report*) ; 
 struct dj_report* kzalloc (int,int /*<<< orphan*/ ) ; 
 int logi_dj_recv_query_hidpp_devices (struct dj_receiver_dev*) ; 
 int logi_dj_recv_send_report (struct dj_receiver_dev*,struct dj_report*) ; 
 scalar_t__ recvr_type_dj ; 

__attribute__((used)) static int logi_dj_recv_query_paired_devices(struct dj_receiver_dev *djrcv_dev)
{
	struct dj_report *dj_report;
	int retval;

	djrcv_dev->last_query = jiffies;

	if (djrcv_dev->type != recvr_type_dj)
		return logi_dj_recv_query_hidpp_devices(djrcv_dev);

	dj_report = kzalloc(sizeof(struct dj_report), GFP_KERNEL);
	if (!dj_report)
		return -ENOMEM;
	dj_report->report_id = REPORT_ID_DJ_SHORT;
	dj_report->device_index = 0xFF;
	dj_report->report_type = REPORT_TYPE_CMD_GET_PAIRED_DEVICES;
	retval = logi_dj_recv_send_report(djrcv_dev, dj_report);
	kfree(dj_report);
	return retval;
}