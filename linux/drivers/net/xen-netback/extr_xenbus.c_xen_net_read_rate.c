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
struct xenbus_device {int /*<<< orphan*/  nodename; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (char*) ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 unsigned long simple_strtoul (char*,char**,int) ; 
 char* xenbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xen_net_read_rate(struct xenbus_device *dev,
			      unsigned long *bytes, unsigned long *usec)
{
	char *s, *e;
	unsigned long b, u;
	char *ratestr;

	/* Default to unlimited bandwidth. */
	*bytes = ~0UL;
	*usec = 0;

	ratestr = xenbus_read(XBT_NIL, dev->nodename, "rate", NULL);
	if (IS_ERR(ratestr))
		return;

	s = ratestr;
	b = simple_strtoul(s, &e, 10);
	if ((s == e) || (*e != ','))
		goto fail;

	s = e + 1;
	u = simple_strtoul(s, &e, 10);
	if ((s == e) || (*e != '\0'))
		goto fail;

	*bytes = b;
	*usec = u;

	kfree(ratestr);
	return;

 fail:
	pr_warn("Failed to parse network rate limit. Traffic unlimited.\n");
	kfree(ratestr);
}