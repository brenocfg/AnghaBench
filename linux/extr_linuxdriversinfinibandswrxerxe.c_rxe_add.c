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
struct rxe_dev {int /*<<< orphan*/  ref_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rxe_dev_put (struct rxe_dev*) ; 
 int rxe_init (struct rxe_dev*) ; 
 int rxe_register_device (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_set_mtu (struct rxe_dev*,unsigned int) ; 

int rxe_add(struct rxe_dev *rxe, unsigned int mtu)
{
	int err;

	kref_init(&rxe->ref_cnt);

	err = rxe_init(rxe);
	if (err)
		goto err1;

	rxe_set_mtu(rxe, mtu);

	err = rxe_register_device(rxe);
	if (err)
		goto err1;

	return 0;

err1:
	rxe_dev_put(rxe);
	return err;
}