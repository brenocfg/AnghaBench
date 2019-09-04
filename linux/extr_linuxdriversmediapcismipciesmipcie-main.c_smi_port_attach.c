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
struct smi_port {int idx; int /*<<< orphan*/  fe_type; struct smi_dev* dev; } ;
struct smi_dev {TYPE_1__* info; } ;
struct TYPE_2__ {int ts_0; int ts_1; int /*<<< orphan*/  fe_1; int /*<<< orphan*/  fe_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  smi_dvb_exit (struct smi_port*) ; 
 int smi_dvb_init (struct smi_port*) ; 
 int smi_fe_init (struct smi_port*) ; 
 int /*<<< orphan*/  smi_port_exit (struct smi_port*) ; 
 int smi_port_init (struct smi_port*,int) ; 

__attribute__((used)) static int smi_port_attach(struct smi_dev *dev,
		struct smi_port *port, int index)
{
	int ret, dmachs;

	port->dev = dev;
	port->idx = index;
	port->fe_type = (index == 0) ? dev->info->fe_0 : dev->info->fe_1;
	dmachs = (index == 0) ? dev->info->ts_0 : dev->info->ts_1;
	/* port init.*/
	ret = smi_port_init(port, dmachs);
	if (ret < 0)
		return ret;
	/* dvb init.*/
	ret = smi_dvb_init(port);
	if (ret < 0)
		goto err_del_port_init;
	/* fe init.*/
	ret = smi_fe_init(port);
	if (ret < 0)
		goto err_del_dvb_init;
	return 0;
err_del_dvb_init:
	smi_dvb_exit(port);
err_del_port_init:
	smi_port_exit(port);
	return ret;
}