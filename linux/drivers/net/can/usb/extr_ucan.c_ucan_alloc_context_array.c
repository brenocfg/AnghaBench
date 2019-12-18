#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int tx_fifo; } ;
struct ucan_priv {int available_tx_urbs; TYPE_1__ device_info; TYPE_2__* context_array; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {int allocated; struct ucan_priv* up; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ucan_release_context_array (struct ucan_priv*) ; 

__attribute__((used)) static int ucan_alloc_context_array(struct ucan_priv *up)
{
	int i;

	/* release contexts if any */
	ucan_release_context_array(up);

	up->context_array = kcalloc(up->device_info.tx_fifo,
				    sizeof(*up->context_array),
				    GFP_KERNEL);
	if (!up->context_array) {
		netdev_err(up->netdev,
			   "Not enough memory to allocate tx contexts\n");
		return -ENOMEM;
	}

	for (i = 0; i < up->device_info.tx_fifo; i++) {
		up->context_array[i].allocated = false;
		up->context_array[i].up = up;
	}

	/* lock is not needed because, driver is currently opening */
	up->available_tx_urbs = up->device_info.tx_fifo;

	return 0;
}