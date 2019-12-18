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
struct iscsi_host {int /*<<< orphan*/  initiatorname; int /*<<< orphan*/  hwaddress; int /*<<< orphan*/  netdev; } ;
struct Scsi_Host {int dummy; } ;
typedef  enum iscsi_host_param { ____Placeholder_iscsi_host_param } iscsi_host_param ;

/* Variables and functions */
 int ENOSYS ; 
#define  ISCSI_HOST_PARAM_HWADDRESS 130 
#define  ISCSI_HOST_PARAM_INITIATOR_NAME 129 
#define  ISCSI_HOST_PARAM_NETDEV_NAME 128 
 int iscsi_switch_str_param (int /*<<< orphan*/ *,char*) ; 
 struct iscsi_host* shost_priv (struct Scsi_Host*) ; 

int iscsi_host_set_param(struct Scsi_Host *shost, enum iscsi_host_param param,
			 char *buf, int buflen)
{
	struct iscsi_host *ihost = shost_priv(shost);

	switch (param) {
	case ISCSI_HOST_PARAM_NETDEV_NAME:
		return iscsi_switch_str_param(&ihost->netdev, buf);
	case ISCSI_HOST_PARAM_HWADDRESS:
		return iscsi_switch_str_param(&ihost->hwaddress, buf);
	case ISCSI_HOST_PARAM_INITIATOR_NAME:
		return iscsi_switch_str_param(&ihost->initiatorname, buf);
	default:
		return -ENOSYS;
	}

	return 0;
}