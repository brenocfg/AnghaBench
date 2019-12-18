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
struct usnic_ib_vf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*,char*) ; 
 int /*<<< orphan*/  usnic_ib_dump_vf (struct usnic_ib_vf*,char*,int) ; 

void usnic_ib_log_vf(struct usnic_ib_vf *vf)
{
	char *buf = kzalloc(1000, GFP_KERNEL);

	if (!buf)
		return;

	usnic_ib_dump_vf(vf, buf, 1000);
	usnic_dbg("%s\n", buf);

	kfree(buf);
}