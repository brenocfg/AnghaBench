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
struct gfar_private {size_t* ftp_rqfpr; size_t* ftp_rqfcr; } ;

/* Variables and functions */
 size_t FPR_FILER_MASK ; 
 size_t RQFCR_AND ; 
 size_t RQFCR_CLE ; 
 size_t RQFCR_CMP_EXACT ; 
 size_t RQFCR_CMP_NOMATCH ; 
 size_t RQFCR_PID_MASK ; 
 size_t RQFCR_PID_PARSE ; 
 int /*<<< orphan*/  gfar_write_filer (struct gfar_private*,size_t,size_t,size_t) ; 

__attribute__((used)) static u32 cluster_entry_per_class(struct gfar_private *priv, u32 rqfar,
				   u32 class)
{
	u32 rqfpr = FPR_FILER_MASK;
	u32 rqfcr = 0x0;

	rqfar--;
	rqfcr = RQFCR_CLE | RQFCR_PID_MASK | RQFCR_CMP_EXACT;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	gfar_write_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_NOMATCH;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	gfar_write_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_EXACT | RQFCR_PID_PARSE | RQFCR_CLE | RQFCR_AND;
	rqfpr = class;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	gfar_write_filer(priv, rqfar, rqfcr, rqfpr);

	rqfar--;
	rqfcr = RQFCR_CMP_EXACT | RQFCR_PID_MASK | RQFCR_AND;
	rqfpr = class;
	priv->ftp_rqfcr[rqfar] = rqfcr;
	priv->ftp_rqfpr[rqfar] = rqfpr;
	gfar_write_filer(priv, rqfar, rqfcr, rqfpr);

	return rqfar;
}