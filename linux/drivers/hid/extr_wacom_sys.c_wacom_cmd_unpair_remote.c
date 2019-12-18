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
struct wacom {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HID_OUTPUT_REPORT ; 
 unsigned char WAC_CMD_DELETE_PAIRING ; 
 int /*<<< orphan*/  WAC_CMD_RETRIES ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (size_t const,int /*<<< orphan*/ ) ; 
 int wacom_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wacom_cmd_unpair_remote(struct wacom *wacom, unsigned char selector)
{
	const size_t buf_size = 2;
	unsigned char *buf;
	int retval;

	buf = kzalloc(buf_size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	buf[0] = WAC_CMD_DELETE_PAIRING;
	buf[1] = selector;

	retval = wacom_set_report(wacom->hdev, HID_OUTPUT_REPORT, buf,
				  buf_size, WAC_CMD_RETRIES);
	kfree(buf);

	return retval;
}