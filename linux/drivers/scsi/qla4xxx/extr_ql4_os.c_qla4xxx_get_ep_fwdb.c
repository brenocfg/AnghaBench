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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {void* sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {void* sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
struct scsi_qla_host {int /*<<< orphan*/  host; } ;
struct iscsi_endpoint {int dummy; } ;
struct dev_db_entry {int options; int /*<<< orphan*/  port; int /*<<< orphan*/  ip_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int DDB_OPT_IPV6_DEVICE ; 
 int /*<<< orphan*/  IP_ADDR_LEN ; 
 int /*<<< orphan*/  IPv6_ADDR_LEN ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_endpoint* qla4xxx_ep_connect (int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (struct sockaddr_storage*) ; 
 struct sockaddr_storage* vmalloc (int) ; 

__attribute__((used)) static struct iscsi_endpoint *qla4xxx_get_ep_fwdb(struct scsi_qla_host *ha,
					struct dev_db_entry *fw_ddb_entry)
{
	struct iscsi_endpoint *ep;
	struct sockaddr_in *addr;
	struct sockaddr_in6 *addr6;
	struct sockaddr *t_addr;
	struct sockaddr_storage *dst_addr;
	char *ip;

	/* TODO: need to destroy on unload iscsi_endpoint*/
	dst_addr = vmalloc(sizeof(*dst_addr));
	if (!dst_addr)
		return NULL;

	if (fw_ddb_entry->options & DDB_OPT_IPV6_DEVICE) {
		t_addr = (struct sockaddr *)dst_addr;
		t_addr->sa_family = AF_INET6;
		addr6 = (struct sockaddr_in6 *)dst_addr;
		ip = (char *)&addr6->sin6_addr;
		memcpy(ip, fw_ddb_entry->ip_addr, IPv6_ADDR_LEN);
		addr6->sin6_port = htons(le16_to_cpu(fw_ddb_entry->port));

	} else {
		t_addr = (struct sockaddr *)dst_addr;
		t_addr->sa_family = AF_INET;
		addr = (struct sockaddr_in *)dst_addr;
		ip = (char *)&addr->sin_addr;
		memcpy(ip, fw_ddb_entry->ip_addr, IP_ADDR_LEN);
		addr->sin_port = htons(le16_to_cpu(fw_ddb_entry->port));
	}

	ep = qla4xxx_ep_connect(ha->host, (struct sockaddr *)dst_addr, 0);
	vfree(dst_addr);
	return ep;
}