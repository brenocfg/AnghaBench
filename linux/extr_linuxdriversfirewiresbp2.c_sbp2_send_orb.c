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
typedef  int /*<<< orphan*/  u64 ;
struct sbp2_pointer {int /*<<< orphan*/  low; scalar_t__ high; } ;
struct sbp2_orb {int /*<<< orphan*/  t; int /*<<< orphan*/  kref; int /*<<< orphan*/  link; struct sbp2_logical_unit* lu; int /*<<< orphan*/  request_bus; } ;
struct sbp2_logical_unit {TYPE_1__* tgt; int /*<<< orphan*/  orb_list; } ;
struct fw_device {int /*<<< orphan*/  max_speed; int /*<<< orphan*/  card; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_WRITE_BLOCK_REQUEST ; 
 int /*<<< orphan*/  complete_transaction ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_send_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sbp2_pointer*,int,int /*<<< orphan*/ ,struct sbp2_orb*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct fw_device* target_parent_device (TYPE_1__*) ; 

__attribute__((used)) static void sbp2_send_orb(struct sbp2_orb *orb, struct sbp2_logical_unit *lu,
			  int node_id, int generation, u64 offset)
{
	struct fw_device *device = target_parent_device(lu->tgt);
	struct sbp2_pointer orb_pointer;
	unsigned long flags;

	orb_pointer.high = 0;
	orb_pointer.low = cpu_to_be32(orb->request_bus);

	orb->lu = lu;
	spin_lock_irqsave(&lu->tgt->lock, flags);
	list_add_tail(&orb->link, &lu->orb_list);
	spin_unlock_irqrestore(&lu->tgt->lock, flags);

	kref_get(&orb->kref); /* transaction callback reference */
	kref_get(&orb->kref); /* orb callback reference */

	fw_send_request(device->card, &orb->t, TCODE_WRITE_BLOCK_REQUEST,
			node_id, generation, device->max_speed, offset,
			&orb_pointer, 8, complete_transaction, orb);
}