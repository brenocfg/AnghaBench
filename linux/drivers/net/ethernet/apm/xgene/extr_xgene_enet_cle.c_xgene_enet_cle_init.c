#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct xgene_cle_ptree {int start_pkt; int num_kn; int num_dbptr; struct xgene_cle_ptree_kn* dbptr; struct xgene_cle_ptree_kn* kn; } ;
struct xgene_enet_cle {struct xgene_cle_ptree ptree; } ;
struct xgene_enet_pdata {scalar_t__ phy_mode; TYPE_4__** rx_ring; int /*<<< orphan*/  ndev; struct xgene_enet_cle cle; } ;
struct xgene_cle_ptree_kn {int cle_priority; int drop; int num_keys; TYPE_3__* key; int /*<<< orphan*/  node_type; void* dstqid; void* nxtfpsel; void* fpsel; } ;
struct xgene_cle_dbptr {int cle_priority; int drop; int num_keys; TYPE_3__* key; int /*<<< orphan*/  node_type; void* dstqid; void* nxtfpsel; void* fpsel; } ;
typedef  int /*<<< orphan*/  kn ;
struct TYPE_8__ {TYPE_2__* page_pool; TYPE_1__* buf_pool; } ;
struct TYPE_7__ {size_t result_pointer; scalar_t__ priority; } ;
struct TYPE_6__ {void* id; } ;
struct TYPE_5__ {void* id; } ;

/* Variables and functions */
 int DB_MAX_PTRS ; 
 size_t DB_RES_ACCEPT ; 
 size_t DB_RES_DEF ; 
 size_t DB_RES_DROP ; 
 int EINVAL ; 
 int /*<<< orphan*/  KN ; 
 scalar_t__ PHY_INTERFACE_MODE_XGMII ; 
 int /*<<< orphan*/  memset (struct xgene_cle_ptree_kn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xgene_cle_setup_def_dbptr (struct xgene_enet_pdata*,struct xgene_enet_cle*,struct xgene_cle_ptree_kn*,size_t,int) ; 
 int xgene_cle_setup_ptree (struct xgene_enet_pdata*,struct xgene_enet_cle*) ; 
 int xgene_cle_setup_rss (struct xgene_enet_pdata*) ; 
 void* xgene_enet_dst_ring_num (TYPE_4__*) ; 
 void* xgene_enet_get_fpsel (void*) ; 

__attribute__((used)) static int xgene_enet_cle_init(struct xgene_enet_pdata *pdata)
{
	struct xgene_enet_cle *enet_cle = &pdata->cle;
	u32 def_qid, def_fpsel, def_nxtfpsel, pool_id;
	struct xgene_cle_dbptr dbptr[DB_MAX_PTRS];
	struct xgene_cle_ptree *ptree;
	struct xgene_cle_ptree_kn kn;
	int ret;

	if (pdata->phy_mode != PHY_INTERFACE_MODE_XGMII)
		return -EINVAL;

	ptree = &enet_cle->ptree;
	ptree->start_pkt = 12; /* Ethertype */

	ret = xgene_cle_setup_rss(pdata);
	if (ret) {
		netdev_err(pdata->ndev, "RSS initialization failed\n");
		return ret;
	}

	def_qid = xgene_enet_dst_ring_num(pdata->rx_ring[0]);
	pool_id = pdata->rx_ring[0]->buf_pool->id;
	def_fpsel = xgene_enet_get_fpsel(pool_id);
	def_nxtfpsel = 0;
	if (pdata->rx_ring[0]->page_pool) {
		pool_id = pdata->rx_ring[0]->page_pool->id;
		def_nxtfpsel = xgene_enet_get_fpsel(pool_id);
	}

	memset(dbptr, 0, sizeof(struct xgene_cle_dbptr) * DB_MAX_PTRS);
	dbptr[DB_RES_ACCEPT].fpsel =  def_fpsel;
	dbptr[DB_RES_ACCEPT].nxtfpsel = def_nxtfpsel;
	dbptr[DB_RES_ACCEPT].dstqid = def_qid;
	dbptr[DB_RES_ACCEPT].cle_priority = 1;

	dbptr[DB_RES_DEF].fpsel = def_fpsel;
	dbptr[DB_RES_DEF].nxtfpsel = def_nxtfpsel;
	dbptr[DB_RES_DEF].dstqid = def_qid;
	dbptr[DB_RES_DEF].cle_priority = 7;
	xgene_cle_setup_def_dbptr(pdata, enet_cle, &dbptr[DB_RES_DEF],
				  DB_RES_ACCEPT, 7);

	dbptr[DB_RES_DROP].drop = 1;

	memset(&kn, 0, sizeof(kn));
	kn.node_type = KN;
	kn.num_keys = 1;
	kn.key[0].priority = 0;
	kn.key[0].result_pointer = DB_RES_ACCEPT;

	ptree->kn = &kn;
	ptree->dbptr = dbptr;
	ptree->num_kn = 1;
	ptree->num_dbptr = DB_MAX_PTRS;

	return xgene_cle_setup_ptree(pdata, enet_cle);
}