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
struct uwb_rsv {TYPE_1__* rc; int /*<<< orphan*/ * owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  uwb_dev; } ;

/* Variables and functions */

__attribute__((used)) static inline bool uwb_rsv_is_owner(struct uwb_rsv *rsv)
{
	return rsv->owner == &rsv->rc->uwb_dev;
}