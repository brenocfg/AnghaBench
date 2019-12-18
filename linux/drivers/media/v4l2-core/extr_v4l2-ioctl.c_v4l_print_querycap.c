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
struct v4l2_capability {int /*<<< orphan*/  device_caps; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_cont (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void v4l_print_querycap(const void *arg, bool write_only)
{
	const struct v4l2_capability *p = arg;

	pr_cont("driver=%.*s, card=%.*s, bus=%.*s, version=0x%08x, capabilities=0x%08x, device_caps=0x%08x\n",
		(int)sizeof(p->driver), p->driver,
		(int)sizeof(p->card), p->card,
		(int)sizeof(p->bus_info), p->bus_info,
		p->version, p->capabilities, p->device_caps);
}