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
struct pcmcia_socket {int /*<<< orphan*/  ops_mutex; scalar_t__ functions; int /*<<< orphan*/ * fake_cis; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_cis_cache (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_bus_add (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  pcmcia_bus_remove (struct pcmcia_socket*) ; 
 int /*<<< orphan*/  verify_cis_cache (struct pcmcia_socket*) ; 

__attribute__((used)) static int pcmcia_bus_early_resume(struct pcmcia_socket *skt)
{
	if (!verify_cis_cache(skt))
		return 0;

	dev_dbg(&skt->dev, "cis mismatch - different card\n");

	/* first, remove the card */
	pcmcia_bus_remove(skt);

	mutex_lock(&skt->ops_mutex);
	destroy_cis_cache(skt);
	kfree(skt->fake_cis);
	skt->fake_cis = NULL;
	skt->functions = 0;
	mutex_unlock(&skt->ops_mutex);

	/* now, add the new card */
	pcmcia_bus_add(skt);
	return 0;
}