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
struct TYPE_2__ {int ipv4_options; int ipv6_options; } ;
struct scsi_qla_host {TYPE_1__ ip_config; } ;

/* Variables and functions */
 int IPOPT_IPV4_PROTOCOL_ENABLE ; 
 int IPV6_OPT_IPV6_PROTOCOL_ENABLE ; 
 int /*<<< orphan*/  qla4xxx_create_ipv4_iface (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4xxx_create_ipv6_iface (struct scsi_qla_host*) ; 

__attribute__((used)) static void qla4xxx_create_ifaces(struct scsi_qla_host *ha)
{
	if (ha->ip_config.ipv4_options & IPOPT_IPV4_PROTOCOL_ENABLE)
		qla4xxx_create_ipv4_iface(ha);

	if (ha->ip_config.ipv6_options & IPV6_OPT_IPV6_PROTOCOL_ENABLE)
		qla4xxx_create_ipv6_iface(ha);
}