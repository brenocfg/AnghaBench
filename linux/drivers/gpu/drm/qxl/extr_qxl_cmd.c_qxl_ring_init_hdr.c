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
struct qxl_ring {int /*<<< orphan*/  n_elements; TYPE_2__* ring; } ;
struct TYPE_3__ {int /*<<< orphan*/  notify_on_prod; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */

void qxl_ring_init_hdr(struct qxl_ring *ring)
{
	ring->ring->header.notify_on_prod = ring->n_elements;
}