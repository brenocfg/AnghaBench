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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u8 ;
struct nlattr {int dummy; } ;
struct iscsi_iface_param_info {int param; int /*<<< orphan*/ * value; } ;
struct beiscsi_hba {int /*<<< orphan*/ * ipv4_iface; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_IP_TYPE_V4 ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EPERM ; 
 int /*<<< orphan*/  ISCSI_BOOTPROTO_DHCP ; 
 int /*<<< orphan*/  ISCSI_BOOTPROTO_STATIC ; 
 int /*<<< orphan*/  ISCSI_IFACE_ENABLE ; 
#define  ISCSI_NET_PARAM_IFACE_ENABLE 132 
#define  ISCSI_NET_PARAM_IPV4_ADDR 131 
#define  ISCSI_NET_PARAM_IPV4_BOOTPROTO 130 
#define  ISCSI_NET_PARAM_IPV4_GW 129 
#define  ISCSI_NET_PARAM_IPV4_SUBNET 128 
 int /*<<< orphan*/  KERN_ERR ; 
 int beiscsi_if_en_dhcp (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int beiscsi_if_en_static (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int beiscsi_if_set_gw (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int beiscsi_iface_create_ipv4 (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_destroy_iface (int /*<<< orphan*/ *) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct iscsi_iface_param_info* nla_data (struct nlattr*) ; 
 struct nlattr* nla_find (void*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int
beiscsi_iface_config_ipv4(struct Scsi_Host *shost,
			  struct iscsi_iface_param_info *info,
			  void *data, uint32_t dt_len)
{
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	u8 *ip = NULL, *subnet = NULL, *gw;
	struct nlattr *nla;
	int ret = -EPERM;

	/* Check the param */
	switch (info->param) {
	case ISCSI_NET_PARAM_IFACE_ENABLE:
		if (info->value[0] == ISCSI_IFACE_ENABLE)
			ret = beiscsi_iface_create_ipv4(phba);
		else {
			iscsi_destroy_iface(phba->ipv4_iface);
			phba->ipv4_iface = NULL;
		}
		break;
	case ISCSI_NET_PARAM_IPV4_GW:
		gw = info->value;
		ret = beiscsi_if_set_gw(phba, BEISCSI_IP_TYPE_V4, gw);
		break;
	case ISCSI_NET_PARAM_IPV4_BOOTPROTO:
		if (info->value[0] == ISCSI_BOOTPROTO_DHCP)
			ret = beiscsi_if_en_dhcp(phba, BEISCSI_IP_TYPE_V4);
		else if (info->value[0] == ISCSI_BOOTPROTO_STATIC)
			/* release DHCP IP address */
			ret = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
						   NULL, NULL);
		else
			beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
				    "BS_%d : Invalid BOOTPROTO: %d\n",
				    info->value[0]);
		break;
	case ISCSI_NET_PARAM_IPV4_ADDR:
		ip = info->value;
		nla = nla_find(data, dt_len, ISCSI_NET_PARAM_IPV4_SUBNET);
		if (nla) {
			info = nla_data(nla);
			subnet = info->value;
		}
		ret = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		break;
	case ISCSI_NET_PARAM_IPV4_SUBNET:
		/*
		 * OPCODE_COMMON_ISCSI_NTWK_MODIFY_IP_ADDR ioctl needs IP
		 * and subnet both. Find IP to be applied for this subnet.
		 */
		subnet = info->value;
		nla = nla_find(data, dt_len, ISCSI_NET_PARAM_IPV4_ADDR);
		if (nla) {
			info = nla_data(nla);
			ip = info->value;
		}
		ret = beiscsi_if_en_static(phba, BEISCSI_IP_TYPE_V4,
					   ip, subnet);
		break;
	}

	return ret;
}