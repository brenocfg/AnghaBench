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
struct t3cdev {int /*<<< orphan*/  name; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CPL_RET_BAD_MSG ; 
 int CPL_RET_BUF_DONE ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_bad_cpl(struct t3cdev *dev, struct sk_buff *skb)
{
	pr_err("%s: received bad CPL command 0x%x\n", dev->name, *skb->data);
	return CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
}