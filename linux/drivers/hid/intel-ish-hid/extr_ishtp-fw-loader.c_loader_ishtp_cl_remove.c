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
struct ishtp_cl_device {int dummy; } ;
struct ishtp_cl_data {int /*<<< orphan*/  work_ishtp_reset; int /*<<< orphan*/  work_fw_load; } ;
struct ishtp_cl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct ishtp_cl_data* ishtp_get_client_data (struct ishtp_cl*) ; 
 struct ishtp_cl* ishtp_get_drvdata (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  ishtp_put_device (struct ishtp_cl_device*) ; 
 int /*<<< orphan*/  loader_deinit (struct ishtp_cl*) ; 

__attribute__((used)) static int loader_ishtp_cl_remove(struct ishtp_cl_device *cl_device)
{
	struct ishtp_cl_data *client_data;
	struct ishtp_cl	*loader_ishtp_cl = ishtp_get_drvdata(cl_device);

	client_data = ishtp_get_client_data(loader_ishtp_cl);

	/*
	 * The sequence of the following two cancel_work_sync() is
	 * important. The work_fw_load can in turn schedue
	 * work_ishtp_reset, so first cancel work_fw_load then
	 * cancel work_ishtp_reset.
	 */
	cancel_work_sync(&client_data->work_fw_load);
	cancel_work_sync(&client_data->work_ishtp_reset);
	loader_deinit(loader_ishtp_cl);
	ishtp_put_device(cl_device);

	return 0;
}