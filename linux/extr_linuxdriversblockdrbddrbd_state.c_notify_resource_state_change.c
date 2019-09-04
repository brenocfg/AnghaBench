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
struct sk_buff {int dummy; } ;
struct resource_info {int /*<<< orphan*/  res_susp_fen; int /*<<< orphan*/  res_susp_nod; int /*<<< orphan*/  res_susp; int /*<<< orphan*/  res_role; } ;
struct drbd_resource_state_change {int /*<<< orphan*/ * susp_fen; int /*<<< orphan*/ * susp_nod; int /*<<< orphan*/ * susp; int /*<<< orphan*/ * role; struct drbd_resource* resource; } ;
struct drbd_resource {int dummy; } ;
typedef  enum drbd_notification_type { ____Placeholder_drbd_notification_type } drbd_notification_type ;

/* Variables and functions */
 size_t NEW ; 
 int /*<<< orphan*/  notify_resource_state (struct sk_buff*,unsigned int,struct drbd_resource*,struct resource_info*,int) ; 

void notify_resource_state_change(struct sk_buff *skb,
				  unsigned int seq,
				  struct drbd_resource_state_change *resource_state_change,
				  enum drbd_notification_type type)
{
	struct drbd_resource *resource = resource_state_change->resource;
	struct resource_info resource_info = {
		.res_role = resource_state_change->role[NEW],
		.res_susp = resource_state_change->susp[NEW],
		.res_susp_nod = resource_state_change->susp_nod[NEW],
		.res_susp_fen = resource_state_change->susp_fen[NEW],
	};

	notify_resource_state(skb, seq, resource, &resource_info, type);
}