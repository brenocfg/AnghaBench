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
typedef  int u32 ;
struct xgene_enet_pdata {int dummy; } ;
struct xgene_cle_dbptr {int drop; int fpsel; int nxtfpsel; int dstqid; int cle_priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLE_DROP ; 
 int /*<<< orphan*/  CLE_DSTQIDH ; 
 int /*<<< orphan*/  CLE_DSTQIDL ; 
 int CLE_DSTQIDL_LEN ; 
 int /*<<< orphan*/  CLE_FPSEL ; 
 int /*<<< orphan*/  CLE_NFPSEL ; 
 int /*<<< orphan*/  CLE_PRIORITY ; 
 int SET_VAL (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_cle_dbptr_to_hw(struct xgene_enet_pdata *pdata,
				  struct xgene_cle_dbptr *dbptr, u32 *buf)
{
	buf[0] = SET_VAL(CLE_DROP, dbptr->drop);
	buf[4] = SET_VAL(CLE_FPSEL, dbptr->fpsel) |
		 SET_VAL(CLE_NFPSEL, dbptr->nxtfpsel) |
		 SET_VAL(CLE_DSTQIDL, dbptr->dstqid);

	buf[5] = SET_VAL(CLE_DSTQIDH, (u32)dbptr->dstqid >> CLE_DSTQIDL_LEN) |
		 SET_VAL(CLE_PRIORITY, dbptr->cle_priority);
}