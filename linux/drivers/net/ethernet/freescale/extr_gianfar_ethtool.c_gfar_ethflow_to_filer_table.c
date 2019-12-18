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
typedef  int u64 ;
struct gfar_private {unsigned int* ftp_rqfpr; unsigned int* ftp_rqfcr; int cur_filer_idx; int /*<<< orphan*/  ndev; } ;

/* Variables and functions */
 unsigned int FPR_FILER_MASK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_FILER_IDX ; 
 int RQFCR_AND ; 
 int RQFCR_CLE ; 
 int RQFCR_CMP_EXACT ; 
 int RQFCR_HASHTBL_0 ; 
 int RQFCR_PID_MASK ; 
 int RQFCR_PID_PARSE ; 
 unsigned int RQFPR_IPV4 ; 
 unsigned int RQFPR_IPV6 ; 
 unsigned int RQFPR_TCP ; 
 unsigned int RQFPR_UDP ; 
#define  TCP_V4_FLOW 131 
#define  TCP_V6_FLOW 130 
#define  UDP_V4_FLOW 129 
#define  UDP_V6_FLOW 128 
 int /*<<< orphan*/  ethflow_to_filer_rules (struct gfar_private*,int) ; 
 int /*<<< orphan*/  gfar_write_filer (struct gfar_private*,int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 unsigned int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int gfar_ethflow_to_filer_table(struct gfar_private *priv, u64 ethflow,
				       u64 class)
{
	unsigned int cmp_rqfpr;
	unsigned int *local_rqfpr;
	unsigned int *local_rqfcr;
	int i = 0x0, k = 0x0;
	int j = MAX_FILER_IDX, l = 0x0;
	int ret = 1;

	local_rqfpr = kmalloc_array(MAX_FILER_IDX + 1, sizeof(unsigned int),
				    GFP_KERNEL);
	local_rqfcr = kmalloc_array(MAX_FILER_IDX + 1, sizeof(unsigned int),
				    GFP_KERNEL);
	if (!local_rqfpr || !local_rqfcr) {
		ret = 0;
		goto err;
	}

	switch (class) {
	case TCP_V4_FLOW:
		cmp_rqfpr = RQFPR_IPV4 |RQFPR_TCP;
		break;
	case UDP_V4_FLOW:
		cmp_rqfpr = RQFPR_IPV4 |RQFPR_UDP;
		break;
	case TCP_V6_FLOW:
		cmp_rqfpr = RQFPR_IPV6 |RQFPR_TCP;
		break;
	case UDP_V6_FLOW:
		cmp_rqfpr = RQFPR_IPV6 |RQFPR_UDP;
		break;
	default:
		netdev_err(priv->ndev,
			   "Right now this class is not supported\n");
		ret = 0;
		goto err;
	}

	for (i = 0; i < MAX_FILER_IDX + 1; i++) {
		local_rqfpr[j] = priv->ftp_rqfpr[i];
		local_rqfcr[j] = priv->ftp_rqfcr[i];
		j--;
		if ((priv->ftp_rqfcr[i] ==
		     (RQFCR_PID_PARSE | RQFCR_CLE | RQFCR_AND)) &&
		    (priv->ftp_rqfpr[i] == cmp_rqfpr))
			break;
	}

	if (i == MAX_FILER_IDX + 1) {
		netdev_err(priv->ndev,
			   "No parse rule found, can't create hash rules\n");
		ret = 0;
		goto err;
	}

	/* If a match was found, then it begins the starting of a cluster rule
	 * if it was already programmed, we need to overwrite these rules
	 */
	for (l = i+1; l < MAX_FILER_IDX; l++) {
		if ((priv->ftp_rqfcr[l] & RQFCR_CLE) &&
		    !(priv->ftp_rqfcr[l] & RQFCR_AND)) {
			priv->ftp_rqfcr[l] = RQFCR_CLE | RQFCR_CMP_EXACT |
					     RQFCR_HASHTBL_0 | RQFCR_PID_MASK;
			priv->ftp_rqfpr[l] = FPR_FILER_MASK;
			gfar_write_filer(priv, l, priv->ftp_rqfcr[l],
					 priv->ftp_rqfpr[l]);
			break;
		}

		if (!(priv->ftp_rqfcr[l] & RQFCR_CLE) &&
			(priv->ftp_rqfcr[l] & RQFCR_AND))
			continue;
		else {
			local_rqfpr[j] = priv->ftp_rqfpr[l];
			local_rqfcr[j] = priv->ftp_rqfcr[l];
			j--;
		}
	}

	priv->cur_filer_idx = l - 1;

	/* hash rules */
	ethflow_to_filer_rules(priv, ethflow);

	/* Write back the popped out rules again */
	for (k = j+1; k < MAX_FILER_IDX; k++) {
		priv->ftp_rqfpr[priv->cur_filer_idx] = local_rqfpr[k];
		priv->ftp_rqfcr[priv->cur_filer_idx] = local_rqfcr[k];
		gfar_write_filer(priv, priv->cur_filer_idx,
				 local_rqfcr[k], local_rqfpr[k]);
		if (!priv->cur_filer_idx)
			break;
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

err:
	kfree(local_rqfcr);
	kfree(local_rqfpr);
	return ret;
}