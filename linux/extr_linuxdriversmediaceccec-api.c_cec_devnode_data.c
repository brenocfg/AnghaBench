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
struct file {struct cec_fh* private_data; } ;
struct cec_fh {TYPE_1__* adap; } ;
struct cec_devnode {int dummy; } ;
struct TYPE_2__ {struct cec_devnode devnode; } ;

/* Variables and functions */

__attribute__((used)) static inline struct cec_devnode *cec_devnode_data(struct file *filp)
{
	struct cec_fh *fh = filp->private_data;

	return &fh->adap->devnode;
}