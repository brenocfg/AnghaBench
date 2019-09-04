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
 int /*<<< orphan*/  rxe_dev_put (struct rxe_dev*) ; 
 int /*<<< orphan*/  rxe_unregister_device (struct rxe_dev*) ; 

void rxe_remove(struct rxe_dev *rxe)
{
	rxe_unregister_device(rxe);

	rxe_dev_put(rxe);
}