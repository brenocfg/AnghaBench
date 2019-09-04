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
struct ishtp_hid_data {size_t index; struct ishtp_cl_data* client_data; } ;
struct ishtp_cl_data {int /*<<< orphan*/ * report_descr_size; int /*<<< orphan*/ * report_descr; } ;
struct hid_device {struct ishtp_hid_data* driver_data; } ;

/* Variables and functions */
 int hid_parse_report (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ishtp_hid_parse(struct hid_device *hid)
{
	struct ishtp_hid_data *hid_data =  hid->driver_data;
	struct ishtp_cl_data *client_data = hid_data->client_data;
	int rv;

	rv = hid_parse_report(hid, client_data->report_descr[hid_data->index],
			      client_data->report_descr_size[hid_data->index]);
	if (rv)
		return	rv;

	return 0;
}