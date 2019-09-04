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
union drbd_state {int /*<<< orphan*/  susp_fen; int /*<<< orphan*/  susp_nod; int /*<<< orphan*/  susp; int /*<<< orphan*/  i; } ;
struct drbd_resource {int /*<<< orphan*/  susp_fen; int /*<<< orphan*/  susp_nod; int /*<<< orphan*/  susp; } ;
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
struct drbd_device {TYPE_1__ state; struct drbd_resource* resource; } ;

/* Variables and functions */

__attribute__((used)) static inline union drbd_state drbd_read_state(struct drbd_device *device)
{
	struct drbd_resource *resource = device->resource;
	union drbd_state rv;

	rv.i = device->state.i;
	rv.susp = resource->susp;
	rv.susp_nod = resource->susp_nod;
	rv.susp_fen = resource->susp_fen;

	return rv;
}