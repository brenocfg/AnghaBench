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
struct fusb300_ep_info {int /*<<< orphan*/  type; int /*<<< orphan*/  epnum; } ;
struct fusb300_ep {int /*<<< orphan*/  type; int /*<<< orphan*/  epnum; } ;

/* Variables and functions */

__attribute__((used)) static void fusb300_ep_setting(struct fusb300_ep *ep,
			       struct fusb300_ep_info info)
{
	ep->epnum = info.epnum;
	ep->type = info.type;
}