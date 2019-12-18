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
struct urb {int dummy; } ;
struct hso_serial {int num_rx_urbs; TYPE_1__* parent; struct urb** rx_urb; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hso_urb_to_index(struct hso_serial *serial, struct urb *urb)
{
	int idx;

	for (idx = 0; idx < serial->num_rx_urbs; idx++)
		if (serial->rx_urb[idx] == urb)
			return idx;
	dev_err(serial->parent->dev, "hso_urb_to_index failed\n");
	return -1;
}