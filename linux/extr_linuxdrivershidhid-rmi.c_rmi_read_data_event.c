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
struct rmi_data {int input_report_size; int /*<<< orphan*/  wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  readReport; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_READ_DATA_PENDING ; 
 int /*<<< orphan*/  RMI_READ_REQUEST_PENDING ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmi_read_data_event(struct hid_device *hdev, u8 *data, int size)
{
	struct rmi_data *hdata = hid_get_drvdata(hdev);

	if (!test_bit(RMI_READ_REQUEST_PENDING, &hdata->flags)) {
		hid_dbg(hdev, "no read request pending\n");
		return 0;
	}

	memcpy(hdata->readReport, data, size < hdata->input_report_size ?
			size : hdata->input_report_size);
	set_bit(RMI_READ_DATA_PENDING, &hdata->flags);
	wake_up(&hdata->wait);

	return 1;
}