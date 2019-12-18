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
struct sockaddr {int dummy; } ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct beiscsi_hba {int /*<<< orphan*/  state; } ;
struct beiscsi_endpoint {struct iscsi_endpoint* openiscsi_ep; struct beiscsi_hba* phba; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_HBA_LINK_UP ; 
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 struct iscsi_endpoint* ERR_PTR (int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  beiscsi_hba_is_online (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int beiscsi_open_conn (struct iscsi_endpoint*,int /*<<< orphan*/ *,struct sockaddr*,int) ; 
 struct iscsi_endpoint* iscsi_create_endpoint (int) ; 
 int /*<<< orphan*/  iscsi_destroy_endpoint (struct iscsi_endpoint*) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

struct iscsi_endpoint *
beiscsi_ep_connect(struct Scsi_Host *shost, struct sockaddr *dst_addr,
		   int non_blocking)
{
	struct beiscsi_hba *phba;
	struct beiscsi_endpoint *beiscsi_ep;
	struct iscsi_endpoint *ep;
	int ret;

	if (!shost) {
		ret = -ENXIO;
		pr_err("beiscsi_ep_connect shost is NULL\n");
		return ERR_PTR(ret);
	}

	phba = iscsi_host_priv(shost);
	if (!beiscsi_hba_is_online(phba)) {
		ret = -EIO;
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
			    "BS_%d : HBA in error 0x%lx\n", phba->state);
		return ERR_PTR(ret);
	}
	if (!test_bit(BEISCSI_HBA_LINK_UP, &phba->state)) {
		ret = -EBUSY;
		beiscsi_log(phba, KERN_WARNING, BEISCSI_LOG_CONFIG,
			    "BS_%d : The Adapter Port state is Down!!!\n");
		return ERR_PTR(ret);
	}

	ep = iscsi_create_endpoint(sizeof(struct beiscsi_endpoint));
	if (!ep) {
		ret = -ENOMEM;
		return ERR_PTR(ret);
	}

	beiscsi_ep = ep->dd_data;
	beiscsi_ep->phba = phba;
	beiscsi_ep->openiscsi_ep = ep;
	ret = beiscsi_open_conn(ep, NULL, dst_addr, non_blocking);
	if (ret) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : Failed in beiscsi_open_conn\n");
		goto free_ep;
	}

	return ep;

free_ep:
	iscsi_destroy_endpoint(ep);
	return ERR_PTR(ret);
}