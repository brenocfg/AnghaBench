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
struct xbox_remote {unsigned char* inbuf; int /*<<< orphan*/  rdev; } ;
struct urb {int actual_length; TYPE_1__* dev; struct xbox_remote* context; } ;
typedef  int /*<<< orphan*/  __le16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RC_PROTO_XBOX_DVD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned char,unsigned char,unsigned char*) ; 
 int /*<<< orphan*/  le16_to_cpup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rc_keydown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xbox_remote_input_report(struct urb *urb)
{
	struct xbox_remote *xbox_remote = urb->context;
	unsigned char *data = xbox_remote->inbuf;

	/*
	 * data[0] = 0x00
	 * data[1] = length - always 0x06
	 * data[2] = the key code
	 * data[3] = high part of key code
	 * data[4] = last_press_ms (low)
	 * data[5] = last_press_ms (high)
	 */

	/* Deal with strange looking inputs */
	if (urb->actual_length != 6 || urb->actual_length != data[1]) {
		dev_warn(&urb->dev->dev, "Weird data, len=%d: %*ph\n",
			 urb->actual_length, urb->actual_length, data);
		return;
	}

	rc_keydown(xbox_remote->rdev, RC_PROTO_XBOX_DVD,
		   le16_to_cpup((__le16 *)(data + 2)), 0);
}