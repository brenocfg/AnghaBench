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
struct ib_umad_packet {int /*<<< orphan*/  list; } ;
struct ib_umad_file {int /*<<< orphan*/  send_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dequeue_send(struct ib_umad_file *file,
			 struct ib_umad_packet *packet)
{
	spin_lock_irq(&file->send_lock);
	list_del(&packet->list);
	spin_unlock_irq(&file->send_lock);
}