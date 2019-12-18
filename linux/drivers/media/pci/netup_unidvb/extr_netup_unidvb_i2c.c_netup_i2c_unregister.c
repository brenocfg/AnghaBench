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
struct netup_unidvb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  netup_i2c_remove (struct netup_unidvb_dev*,int) ; 

void netup_i2c_unregister(struct netup_unidvb_dev *ndev)
{
	netup_i2c_remove(ndev, 0);
	netup_i2c_remove(ndev, 1);
}