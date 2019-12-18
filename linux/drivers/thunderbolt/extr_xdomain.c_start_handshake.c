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
struct tb_xdomain {int /*<<< orphan*/  get_properties_work; TYPE_1__* tb; int /*<<< orphan*/  properties_changed_work; int /*<<< orphan*/  get_uuid_work; scalar_t__ needs_uuid; int /*<<< orphan*/  properties_changed_retries; int /*<<< orphan*/  properties_retries; int /*<<< orphan*/  uuid_retries; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  XDOMAIN_PROPERTIES_CHANGED_RETRIES ; 
 int /*<<< orphan*/  XDOMAIN_PROPERTIES_RETRIES ; 
 int /*<<< orphan*/  XDOMAIN_UUID_RETRIES ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_handshake(struct tb_xdomain *xd)
{
	xd->uuid_retries = XDOMAIN_UUID_RETRIES;
	xd->properties_retries = XDOMAIN_PROPERTIES_RETRIES;
	xd->properties_changed_retries = XDOMAIN_PROPERTIES_CHANGED_RETRIES;

	if (xd->needs_uuid) {
		queue_delayed_work(xd->tb->wq, &xd->get_uuid_work,
				   msecs_to_jiffies(100));
	} else {
		/* Start exchanging properties with the other host */
		queue_delayed_work(xd->tb->wq, &xd->properties_changed_work,
				   msecs_to_jiffies(100));
		queue_delayed_work(xd->tb->wq, &xd->get_properties_work,
				   msecs_to_jiffies(1000));
	}
}