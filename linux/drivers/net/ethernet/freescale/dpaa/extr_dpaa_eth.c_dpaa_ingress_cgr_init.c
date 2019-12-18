#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {void* cstd_en; int /*<<< orphan*/  cs_thres; void* cscn_en; } ;
struct qm_mcc_initcgr {TYPE_1__ cgr; int /*<<< orphan*/  we_mask; } ;
struct TYPE_6__ {int /*<<< orphan*/  cgrid; } ;
struct dpaa_priv {int use_ingress_cgr; TYPE_2__* mac_dev; TYPE_3__ ingress_cgr; } ;
typedef  int /*<<< orphan*/  initcgr ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPAA_INGRESS_CS_THRESHOLD ; 
 int /*<<< orphan*/  QMAN_CGR_FLAG_USE_INIT ; 
 void* QM_CGR_EN ; 
 int /*<<< orphan*/  QM_CGR_WE_CSTD_EN ; 
 int /*<<< orphan*/  QM_CGR_WE_CS_THRES ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qm_mcc_initcgr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_drv (struct dpaa_priv*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  qm_cgr_cs_thres_set64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int qman_alloc_cgrid (int /*<<< orphan*/ *) ; 
 int qman_create_cgr (TYPE_3__*,int /*<<< orphan*/ ,struct qm_mcc_initcgr*) ; 
 int /*<<< orphan*/  qman_release_cgrid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpaa_ingress_cgr_init(struct dpaa_priv *priv)
{
	struct qm_mcc_initcgr initcgr;
	u32 cs_th;
	int err;

	err = qman_alloc_cgrid(&priv->ingress_cgr.cgrid);
	if (err < 0) {
		if (netif_msg_drv(priv))
			pr_err("Error %d allocating CGR ID\n", err);
		goto out_error;
	}

	/* Enable CS TD, but disable Congestion State Change Notifications. */
	memset(&initcgr, 0, sizeof(initcgr));
	initcgr.we_mask = cpu_to_be16(QM_CGR_WE_CS_THRES);
	initcgr.cgr.cscn_en = QM_CGR_EN;
	cs_th = DPAA_INGRESS_CS_THRESHOLD;
	qm_cgr_cs_thres_set64(&initcgr.cgr.cs_thres, cs_th, 1);

	initcgr.we_mask |= cpu_to_be16(QM_CGR_WE_CSTD_EN);
	initcgr.cgr.cstd_en = QM_CGR_EN;

	/* This CGR will be associated with the SWP affined to the current CPU.
	 * However, we'll place all our ingress FQs in it.
	 */
	err = qman_create_cgr(&priv->ingress_cgr, QMAN_CGR_FLAG_USE_INIT,
			      &initcgr);
	if (err < 0) {
		if (netif_msg_drv(priv))
			pr_err("Error %d creating ingress CGR with ID %d\n",
			       err, priv->ingress_cgr.cgrid);
		qman_release_cgrid(priv->ingress_cgr.cgrid);
		goto out_error;
	}
	if (netif_msg_drv(priv))
		pr_debug("Created ingress CGR %d for netdev with hwaddr %pM\n",
			 priv->ingress_cgr.cgrid, priv->mac_dev->addr);

	priv->use_ingress_cgr = true;

out_error:
	return err;
}