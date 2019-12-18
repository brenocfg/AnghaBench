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
struct uverbs_attr_bundle {int /*<<< orphan*/  driver_udata; } ;
struct ib_uverbs_create_xsrq {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int __uverbs_create_xsrq (struct uverbs_attr_bundle*,struct ib_uverbs_create_xsrq*,int /*<<< orphan*/ *) ; 
 int uverbs_request (struct uverbs_attr_bundle*,struct ib_uverbs_create_xsrq*,int) ; 

__attribute__((used)) static int ib_uverbs_create_xsrq(struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_create_xsrq     cmd;
	int ret;

	ret = uverbs_request(attrs, &cmd, sizeof(cmd));
	if (ret)
		return ret;

	return __uverbs_create_xsrq(attrs, &cmd, &attrs->driver_udata);
}