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
struct hci_uart {struct h5* priv; } ;
struct h5 {TYPE_1__* vnd; } ;
struct TYPE_2__ {int (* setup ) (struct h5*) ;} ;

/* Variables and functions */
 int stub1 (struct h5*) ; 

__attribute__((used)) static int h5_setup(struct hci_uart *hu)
{
	struct h5 *h5 = hu->priv;

	if (h5->vnd && h5->vnd->setup)
		return h5->vnd->setup(h5);

	return 0;
}