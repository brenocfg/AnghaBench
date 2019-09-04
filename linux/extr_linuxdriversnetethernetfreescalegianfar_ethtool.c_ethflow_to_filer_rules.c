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
typedef  void* u32 ;
struct gfar_private {size_t cur_filer_idx; void** ftp_rqfcr; void** ftp_rqfpr; } ;

/* Variables and functions */
 void* FPR_FILER_MASK ; 
 int RQFCR_AND ; 
 int RQFCR_CMP_NOMATCH ; 
 int RQFCR_HASH ; 
 int RQFCR_HASHTBL_0 ; 
 int RQFCR_PID_DAH ; 
 int RQFCR_PID_DAL ; 
 int RQFCR_PID_DIA ; 
 int RQFCR_PID_DPT ; 
 int RQFCR_PID_L4P ; 
 int RQFCR_PID_SIA ; 
 int RQFCR_PID_SPT ; 
 int RQFCR_PID_VID ; 
 int RXH_IP_DST ; 
 int RXH_IP_SRC ; 
 int RXH_L2DA ; 
 int RXH_L3_PROTO ; 
 int RXH_L4_B_0_1 ; 
 int RXH_L4_B_2_3 ; 
 int RXH_VLAN ; 
 int /*<<< orphan*/  gfar_write_filer (struct gfar_private*,size_t,void*,void*) ; 

__attribute__((used)) static void ethflow_to_filer_rules (struct gfar_private *priv, u64 ethflow)
{
	u32 fcr = 0x0, fpr = FPR_FILER_MASK;

	if (ethflow & RXH_L2DA) {
		fcr = RQFCR_PID_DAH | RQFCR_CMP_NOMATCH |
		      RQFCR_HASH | RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;

		fcr = RQFCR_PID_DAL | RQFCR_CMP_NOMATCH |
		      RQFCR_HASH | RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & RXH_VLAN) {
		fcr = RQFCR_PID_VID | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & RXH_IP_SRC) {
		fcr = RQFCR_PID_SIA | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & (RXH_IP_DST)) {
		fcr = RQFCR_PID_DIA | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & RXH_L3_PROTO) {
		fcr = RQFCR_PID_L4P | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & RXH_L4_B_0_1) {
		fcr = RQFCR_PID_SPT | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}

	if (ethflow & RXH_L4_B_2_3) {
		fcr = RQFCR_PID_DPT | RQFCR_CMP_NOMATCH | RQFCR_HASH |
		      RQFCR_AND | RQFCR_HASHTBL_0;
		priv->ftp_rqfpr[priv->cur_filer_idx] = fpr;
		priv->ftp_rqfcr[priv->cur_filer_idx] = fcr;
		gfar_write_filer(priv, priv->cur_filer_idx, fcr, fpr);
		priv->cur_filer_idx = priv->cur_filer_idx - 1;
	}
}