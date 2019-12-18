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
struct pcmcia_socket {int /*<<< orphan*/  ops_mutex; scalar_t__ pcmcia_pfc; int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  destroy_cis_cache (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_card_add (struct pcmcia_socket*) ; 

__attribute__((used)) static int pcmcia_bus_add(struct pcmcia_socket *skt)
{
	atomic_set(&skt->present, 1);

	mutex_lock(&skt->ops_mutex);
	skt->pcmcia_pfc = 0;
	destroy_cis_cache(skt); /* to be on the safe side... */
	mutex_unlock(&skt->ops_mutex);

	pcmcia_card_add(skt);

	return 0;
}