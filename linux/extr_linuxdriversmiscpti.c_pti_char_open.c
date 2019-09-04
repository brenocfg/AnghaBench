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
struct pti_masterchannel {int dummy; } ;
struct inode {int dummy; } ;
struct file {struct pti_masterchannel* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct pti_masterchannel* pti_request_masterchannel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pti_char_open(struct inode *inode, struct file *filp)
{
	struct pti_masterchannel *mc;

	/*
	 * We really do want to fail immediately if
	 * pti_request_masterchannel() fails,
	 * before assigning the value to filp->private_data.
	 * Slightly easier to debug if this driver needs debugging.
	 */
	mc = pti_request_masterchannel(0, NULL);
	if (mc == NULL)
		return -ENOMEM;
	filp->private_data = mc;
	return 0;
}