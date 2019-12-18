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
typedef  int u8 ;
struct cp2112_write_req_report {int slave_address; int length; int* data; int /*<<< orphan*/  report; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP2112_DATA_WRITE_REQUEST ; 
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static int cp2112_write_req(void *buf, u8 slave_address, u8 command, u8 *data,
			    u8 data_length)
{
	struct cp2112_write_req_report *report = buf;

	if (data_length > sizeof(report->data) - 1)
		return -EINVAL;

	report->report = CP2112_DATA_WRITE_REQUEST;
	report->slave_address = slave_address << 1;
	report->length = data_length + 1;
	report->data[0] = command;
	memcpy(&report->data[1], data, data_length);
	return data_length + 4;
}