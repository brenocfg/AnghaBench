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
typedef  size_t u32 ;
struct xgene_enet_pdata {int dummy; } ;
struct xgene_cle_ptree {size_t num_dbptr; scalar_t__ start_dbptr; int /*<<< orphan*/ * dbptr; } ;
struct xgene_enet_cle {struct xgene_cle_ptree ptree; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_CMD_WR ; 
 int CLE_DRAM_REGS ; 
 int /*<<< orphan*/  DB_RAM ; 
 int /*<<< orphan*/  memset (size_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_cle_dbptr_to_hw (struct xgene_enet_pdata*,int /*<<< orphan*/ *,size_t*) ; 
 int xgene_cle_dram_wr (struct xgene_enet_cle*,size_t*,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_cle_setup_dbptr(struct xgene_enet_pdata *pdata,
				 struct xgene_enet_cle *cle)
{
	struct xgene_cle_ptree *ptree = &cle->ptree;
	u32 buf[CLE_DRAM_REGS];
	u32 i;
	int ret;

	memset(buf, 0, sizeof(buf));
	for (i = 0; i < ptree->num_dbptr; i++) {
		xgene_cle_dbptr_to_hw(pdata, &ptree->dbptr[i], buf);
		ret = xgene_cle_dram_wr(cle, buf, 6, i + ptree->start_dbptr,
					DB_RAM,	CLE_CMD_WR);
		if (ret)
			return ret;
	}

	return 0;
}