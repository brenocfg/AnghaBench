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
struct zfcp_fc_wka_ports {int /*<<< orphan*/  as; int /*<<< orphan*/  ds; int /*<<< orphan*/  ts; int /*<<< orphan*/  ms; } ;
struct zfcp_adapter {struct zfcp_fc_wka_ports* gs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FC_FID_ALIASES ; 
 int /*<<< orphan*/  FC_FID_DIR_SERV ; 
 int /*<<< orphan*/  FC_FID_MGMT_SERV ; 
 int /*<<< orphan*/  FC_FID_TIME_SERV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct zfcp_fc_wka_ports* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fc_wka_port_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zfcp_adapter*) ; 

int zfcp_fc_gs_setup(struct zfcp_adapter *adapter)
{
	struct zfcp_fc_wka_ports *wka_ports;

	wka_ports = kzalloc(sizeof(struct zfcp_fc_wka_ports), GFP_KERNEL);
	if (!wka_ports)
		return -ENOMEM;

	adapter->gs = wka_ports;
	zfcp_fc_wka_port_init(&wka_ports->ms, FC_FID_MGMT_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->ts, FC_FID_TIME_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->ds, FC_FID_DIR_SERV, adapter);
	zfcp_fc_wka_port_init(&wka_ports->as, FC_FID_ALIASES, adapter);

	return 0;
}