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
struct uwb_rceb {int /*<<< orphan*/  bEventContext; int /*<<< orphan*/  wEvent; int /*<<< orphan*/  bEventType; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ENOSPC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,size_t const) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ssize_t hwarc_get_event_size(struct uwb_rc *rc, const struct uwb_rceb *rceb,
			     size_t core_size, size_t offset,
			     const size_t buf_size)
{
	ssize_t size = -ENOSPC;
	const void *ptr = rceb;
	size_t type_size = sizeof(__le16);
	struct device *dev = &rc->uwb_dev.dev;

	if (offset + type_size >= buf_size) {
		dev_err(dev, "Not enough data to read extra size of event "
			"0x%02x/%04x/%02x, only got %zu bytes.\n",
			rceb->bEventType, le16_to_cpu(rceb->wEvent),
			rceb->bEventContext, buf_size);
		goto out;
	}
	ptr += offset;
	size = core_size + le16_to_cpu(*(__le16 *)ptr);
out:
	return size;
}