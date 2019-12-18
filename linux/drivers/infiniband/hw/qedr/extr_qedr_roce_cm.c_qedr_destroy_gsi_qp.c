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
struct qedr_dev {int dummy; } ;

/* Variables and functions */
 int qedr_ll2_stop (struct qedr_dev*) ; 

int qedr_destroy_gsi_qp(struct qedr_dev *dev)
{
	return qedr_ll2_stop(dev);
}