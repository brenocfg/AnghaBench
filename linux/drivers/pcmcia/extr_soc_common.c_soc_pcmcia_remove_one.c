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
struct soc_pcmcia_socket {int /*<<< orphan*/  res_skt; int /*<<< orphan*/  res_io; int /*<<< orphan*/  res_mem; int /*<<< orphan*/  res_attr; int /*<<< orphan*/ * virt_io; int /*<<< orphan*/  cpufreq_nb; TYPE_1__* ops; int /*<<< orphan*/  socket; int /*<<< orphan*/  poll_timer; } ;
struct TYPE_2__ {scalar_t__ frequency_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int /*<<< orphan*/  cpufreq_unregister_notifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_common_pcmcia_config_skt (struct soc_pcmcia_socket*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soc_pcmcia_hw_shutdown (struct soc_pcmcia_socket*) ; 

void soc_pcmcia_remove_one(struct soc_pcmcia_socket *skt)
{
	del_timer_sync(&skt->poll_timer);

	pcmcia_unregister_socket(&skt->socket);

#ifdef CONFIG_CPU_FREQ
	if (skt->ops->frequency_change)
		cpufreq_unregister_notifier(&skt->cpufreq_nb,
					    CPUFREQ_TRANSITION_NOTIFIER);
#endif

	soc_pcmcia_hw_shutdown(skt);

	/* should not be required; violates some lowlevel drivers */
	soc_common_pcmcia_config_skt(skt, &dead_socket);

	iounmap(skt->virt_io);
	skt->virt_io = NULL;
	release_resource(&skt->res_attr);
	release_resource(&skt->res_mem);
	release_resource(&skt->res_io);
	release_resource(&skt->res_skt);
}