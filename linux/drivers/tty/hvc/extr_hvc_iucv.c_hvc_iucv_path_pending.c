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
typedef  int /*<<< orphan*/  wildcard ;
typedef  char u8 ;
struct iucv_path {int msglim; int /*<<< orphan*/  flags; } ;
struct hvc_iucv_private {scalar_t__ iucv_state; char* srv_name; char* info_path; int /*<<< orphan*/  lock; int /*<<< orphan*/  sndbuf_work; struct iucv_path* path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASCEBC (char*,int) ; 
 int ENODEV ; 
 scalar_t__ IUCV_CONNECTED ; 
 scalar_t__ IUCV_DISCONN ; 
 int /*<<< orphan*/  IUCV_IPRMDATA ; 
 int hvc_iucv_devices ; 
 int hvc_iucv_filter_connreq (char*) ; 
 int /*<<< orphan*/  hvc_iucv_filter_lock ; 
 int /*<<< orphan*/  hvc_iucv_handler ; 
 struct hvc_iucv_private** hvc_iucv_table ; 
 int iucv_path_accept (struct iucv_path*,int /*<<< orphan*/ *,char*,struct hvc_iucv_private*) ; 
 int /*<<< orphan*/  iucv_path_free (struct iucv_path*) ; 
 int /*<<< orphan*/  iucv_path_sever (struct iucv_path*,char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static	int hvc_iucv_path_pending(struct iucv_path *path, u8 *ipvmid,
				  u8 *ipuser)
{
	struct hvc_iucv_private *priv, *tmp;
	u8 wildcard[9] = "lnxhvc  ";
	int i, rc, find_unused;
	u8 nuser_data[16];
	u8 vm_user_id[9];

	ASCEBC(wildcard, sizeof(wildcard));
	find_unused = !memcmp(wildcard, ipuser, 8);

	/* First, check if the pending path request is managed by this
	 * IUCV handler:
	 * - find a disconnected device if ipuser contains the wildcard
	 * - find the device that matches the terminal ID in ipuser
	 */
	priv = NULL;
	for (i = 0; i < hvc_iucv_devices; i++) {
		tmp = hvc_iucv_table[i];
		if (!tmp)
			continue;

		if (find_unused) {
			spin_lock(&tmp->lock);
			if (tmp->iucv_state == IUCV_DISCONN)
				priv = tmp;
			spin_unlock(&tmp->lock);

		} else if (!memcmp(tmp->srv_name, ipuser, 8))
				priv = tmp;
		if (priv)
			break;
	}
	if (!priv)
		return -ENODEV;

	/* Enforce that ipvmid is allowed to connect to us */
	read_lock(&hvc_iucv_filter_lock);
	rc = hvc_iucv_filter_connreq(ipvmid);
	read_unlock(&hvc_iucv_filter_lock);
	if (rc) {
		iucv_path_sever(path, ipuser);
		iucv_path_free(path);
		memcpy(vm_user_id, ipvmid, 8);
		vm_user_id[8] = 0;
		pr_info("A connection request from z/VM user ID %s "
			"was refused\n", vm_user_id);
		return 0;
	}

	spin_lock(&priv->lock);

	/* If the terminal is already connected or being severed, then sever
	 * this path to enforce that there is only ONE established communication
	 * path per terminal. */
	if (priv->iucv_state != IUCV_DISCONN) {
		iucv_path_sever(path, ipuser);
		iucv_path_free(path);
		goto out_path_handled;
	}

	/* accept path */
	memcpy(nuser_data, ipuser + 8, 8);  /* remote service (for af_iucv) */
	memcpy(nuser_data + 8, ipuser, 8);  /* local service  (for af_iucv) */
	path->msglim = 0xffff;		    /* IUCV MSGLIMIT */
	path->flags &= ~IUCV_IPRMDATA;	    /* TODO: use IUCV_IPRMDATA */
	rc = iucv_path_accept(path, &hvc_iucv_handler, nuser_data, priv);
	if (rc) {
		iucv_path_sever(path, ipuser);
		iucv_path_free(path);
		goto out_path_handled;
	}
	priv->path = path;
	priv->iucv_state = IUCV_CONNECTED;

	/* store path information */
	memcpy(priv->info_path, ipvmid, 8);
	memcpy(priv->info_path + 8, ipuser + 8, 8);

	/* flush buffered output data... */
	schedule_delayed_work(&priv->sndbuf_work, 5);

out_path_handled:
	spin_unlock(&priv->lock);
	return 0;
}