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
struct rxe_dev {int dummy; } ;

/* Variables and functions */
 int rxe_init (struct rxe_dev*) ; 
 int rxe_register_device (struct rxe_dev*,char const*) ; 
 int /*<<< orphan*/  rxe_set_mtu (struct rxe_dev*,unsigned int) ; 

int rxe_add(struct rxe_dev *rxe, unsigned int mtu, const char *ibdev_name)
{
	int err;

	err = rxe_init(rxe);
	if (err)
		return err;

	rxe_set_mtu(rxe, mtu);

	return rxe_register_device(rxe, ibdev_name);
}