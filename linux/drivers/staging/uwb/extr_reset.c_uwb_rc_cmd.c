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
struct uwb_rceb {int /*<<< orphan*/  wEvent; int /*<<< orphan*/  bEventType; } ;
struct uwb_rccb {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EIO ; 
 size_t __uwb_rc_cmd (struct uwb_rc*,char const*,struct uwb_rccb*,size_t,struct uwb_rceb*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,size_t,size_t) ; 

ssize_t uwb_rc_cmd(struct uwb_rc *rc, const char *cmd_name,
		   struct uwb_rccb *cmd, size_t cmd_size,
		   struct uwb_rceb *reply, size_t reply_size)
{
	struct device *dev = &rc->uwb_dev.dev;
	ssize_t result;

	result = __uwb_rc_cmd(rc, cmd_name,
			      cmd, cmd_size, reply, reply_size,
			      reply->bEventType, reply->wEvent, NULL);

	if (result > 0 && result < reply_size) {
		dev_err(dev, "%s: not enough data returned for decoding reply "
			"(%zu bytes received vs at least %zu needed)\n",
			cmd_name, result, reply_size);
		result = -EIO;
	}
	return result;
}