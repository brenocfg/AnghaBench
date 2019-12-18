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
struct dasd_ccw_req {int /*<<< orphan*/  irb; int /*<<< orphan*/  intrc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOLINK ; 
 int /*<<< orphan*/  EPERM ; 
 char* dasd_get_sense (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
suborder_not_supported(struct dasd_ccw_req *cqr)
{
	char *sense;
	char reason;
	char msg_format;
	char msg_no;

	/*
	 * intrc values ENODEV, ENOLINK and EPERM
	 * will be optained from sleep_on to indicate that no
	 * IO operation can be started
	 */
	if (cqr->intrc == -ENODEV)
		return 1;

	if (cqr->intrc == -ENOLINK)
		return 1;

	if (cqr->intrc == -EPERM)
		return 1;

	sense = dasd_get_sense(&cqr->irb);
	if (!sense)
		return 0;

	reason = sense[0];
	msg_format = (sense[7] & 0xF0);
	msg_no = (sense[7] & 0x0F);

	/* command reject, Format 0 MSG 4 - invalid parameter */
	if ((reason == 0x80) && (msg_format == 0x00) && (msg_no == 0x04))
		return 1;

	return 0;
}