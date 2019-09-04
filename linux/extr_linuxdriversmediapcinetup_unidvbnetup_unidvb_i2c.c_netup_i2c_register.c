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
 int netup_i2c_init (struct netup_unidvb_dev*,int) ; 
 int /*<<< orphan*/  netup_i2c_remove (struct netup_unidvb_dev*,int /*<<< orphan*/ ) ; 

int netup_i2c_register(struct netup_unidvb_dev *ndev)
{
	int ret;

	ret = netup_i2c_init(ndev, 0);
	if (ret)
		return ret;
	ret = netup_i2c_init(ndev, 1);
	if (ret) {
		netup_i2c_remove(ndev, 0);
		return ret;
	}
	return 0;
}