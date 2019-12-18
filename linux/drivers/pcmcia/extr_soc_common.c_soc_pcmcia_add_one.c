#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  start; } ;
struct TYPE_17__ {int /*<<< orphan*/  parent; } ;
struct TYPE_16__ {int features; unsigned long io_offset; TYPE_9__ dev; int /*<<< orphan*/  map_size; scalar_t__ irq_mask; int /*<<< orphan*/ * resource_ops; int /*<<< orphan*/ * ops; } ;
struct TYPE_14__ {scalar_t__ expires; } ;
struct TYPE_12__ {int /*<<< orphan*/  notifier_call; } ;
struct soc_pcmcia_socket {TYPE_3__ res_skt; TYPE_3__ res_io; TYPE_3__ res_mem; TYPE_3__ res_attr; int /*<<< orphan*/ * virt_io; TYPE_6__ socket; TYPE_2__ poll_timer; TYPE_11__ cpufreq_nb; TYPE_1__* ops; int /*<<< orphan*/  status; int /*<<< orphan*/  cs_state; } ;
struct TYPE_13__ {scalar_t__ frequency_change; int /*<<< orphan*/  (* set_timing ) (struct soc_pcmcia_socket*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_TRANSITION_NOTIFIER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ SOC_PCMCIA_POLL_PERIOD ; 
 int SS_CAP_PCCARD ; 
 int SS_CAP_STATIC_MAP ; 
 int cpufreq_register_notifier (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead_socket ; 
 int /*<<< orphan*/  del_timer_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_attr_status ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_create_file (TYPE_9__*,int /*<<< orphan*/ *) ; 
 TYPE_3__ iomem_resource ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pccard_static_ops ; 
 int pcmcia_register_socket (TYPE_6__*) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (TYPE_6__*) ; 
 int /*<<< orphan*/  release_resource (TYPE_3__*) ; 
 int request_resource (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  soc_common_pcmcia_cpufreq_nb ; 
 int /*<<< orphan*/  soc_common_pcmcia_operations ; 
 int /*<<< orphan*/  soc_common_pcmcia_poll_event ; 
 int /*<<< orphan*/  soc_common_pcmcia_skt_state (struct soc_pcmcia_socket*) ; 
 int soc_pcmcia_hw_init (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  soc_pcmcia_hw_shutdown (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  stub1 (struct soc_pcmcia_socket*) ; 
 int /*<<< orphan*/  timer_setup (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int soc_pcmcia_add_one(struct soc_pcmcia_socket *skt)
{
	int ret;

	skt->cs_state = dead_socket;

	timer_setup(&skt->poll_timer, soc_common_pcmcia_poll_event, 0);
	skt->poll_timer.expires = jiffies + SOC_PCMCIA_POLL_PERIOD;

	ret = request_resource(&iomem_resource, &skt->res_skt);
	if (ret)
		goto out_err_1;

	ret = request_resource(&skt->res_skt, &skt->res_io);
	if (ret)
		goto out_err_2;

	ret = request_resource(&skt->res_skt, &skt->res_mem);
	if (ret)
		goto out_err_3;

	ret = request_resource(&skt->res_skt, &skt->res_attr);
	if (ret)
		goto out_err_4;

	skt->virt_io = ioremap(skt->res_io.start, 0x10000);
	if (skt->virt_io == NULL) {
		ret = -ENOMEM;
		goto out_err_5;
	}

	/*
	 * We initialize default socket timing here, because
	 * we are not guaranteed to see a SetIOMap operation at
	 * runtime.
	 */
	skt->ops->set_timing(skt);

	ret = soc_pcmcia_hw_init(skt);
	if (ret)
		goto out_err_6;

	skt->socket.ops = &soc_common_pcmcia_operations;
	skt->socket.features = SS_CAP_STATIC_MAP|SS_CAP_PCCARD;
	skt->socket.resource_ops = &pccard_static_ops;
	skt->socket.irq_mask = 0;
	skt->socket.map_size = PAGE_SIZE;
	skt->socket.io_offset = (unsigned long)skt->virt_io;

	skt->status = soc_common_pcmcia_skt_state(skt);

#ifdef CONFIG_CPU_FREQ
	if (skt->ops->frequency_change) {
		skt->cpufreq_nb.notifier_call = soc_common_pcmcia_cpufreq_nb;

		ret = cpufreq_register_notifier(&skt->cpufreq_nb,
						CPUFREQ_TRANSITION_NOTIFIER);
		if (ret < 0)
			dev_err(skt->socket.dev.parent,
				"unable to register CPU frequency change notifier for PCMCIA (%d)\n",
				ret);
	}
#endif

	ret = pcmcia_register_socket(&skt->socket);
	if (ret)
		goto out_err_7;

	ret = device_create_file(&skt->socket.dev, &dev_attr_status);
	if (ret)
		goto out_err_8;

	return ret;

 out_err_8:
	del_timer_sync(&skt->poll_timer);
	pcmcia_unregister_socket(&skt->socket);

 out_err_7:
	soc_pcmcia_hw_shutdown(skt);
 out_err_6:
	iounmap(skt->virt_io);
 out_err_5:
	release_resource(&skt->res_attr);
 out_err_4:
	release_resource(&skt->res_mem);
 out_err_3:
	release_resource(&skt->res_io);
 out_err_2:
	release_resource(&skt->res_skt);
 out_err_1:

	return ret;
}