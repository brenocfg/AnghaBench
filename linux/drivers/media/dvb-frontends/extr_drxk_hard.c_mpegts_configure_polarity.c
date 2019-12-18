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
typedef  int u16 ;
struct drxk_state {scalar_t__ m_invert_clk; scalar_t__ m_invert_val; scalar_t__ m_invert_str; scalar_t__ m_invert_err; scalar_t__ m_invert_data; } ;

/* Variables and functions */
 int FEC_OC_IPR_INVERT_MCLK__M ; 
 int FEC_OC_IPR_INVERT_MD0__M ; 
 int FEC_OC_IPR_INVERT_MD1__M ; 
 int FEC_OC_IPR_INVERT_MD2__M ; 
 int FEC_OC_IPR_INVERT_MD3__M ; 
 int FEC_OC_IPR_INVERT_MD4__M ; 
 int FEC_OC_IPR_INVERT_MD5__M ; 
 int FEC_OC_IPR_INVERT_MD6__M ; 
 int FEC_OC_IPR_INVERT_MD7__M ; 
 int FEC_OC_IPR_INVERT_MERR__M ; 
 int FEC_OC_IPR_INVERT_MSTRT__M ; 
 int FEC_OC_IPR_INVERT_MVAL__M ; 
 int /*<<< orphan*/  FEC_OC_IPR_INVERT__A ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int write16 (struct drxk_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mpegts_configure_polarity(struct drxk_state *state)
{
	u16 fec_oc_reg_ipr_invert = 0;

	/* Data mask for the output data byte */
	u16 invert_data_mask =
	    FEC_OC_IPR_INVERT_MD7__M | FEC_OC_IPR_INVERT_MD6__M |
	    FEC_OC_IPR_INVERT_MD5__M | FEC_OC_IPR_INVERT_MD4__M |
	    FEC_OC_IPR_INVERT_MD3__M | FEC_OC_IPR_INVERT_MD2__M |
	    FEC_OC_IPR_INVERT_MD1__M | FEC_OC_IPR_INVERT_MD0__M;

	dprintk(1, "\n");

	/* Control selective inversion of output bits */
	fec_oc_reg_ipr_invert &= (~(invert_data_mask));
	if (state->m_invert_data)
		fec_oc_reg_ipr_invert |= invert_data_mask;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MERR__M));
	if (state->m_invert_err)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MERR__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MSTRT__M));
	if (state->m_invert_str)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MSTRT__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MVAL__M));
	if (state->m_invert_val)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MVAL__M;
	fec_oc_reg_ipr_invert &= (~(FEC_OC_IPR_INVERT_MCLK__M));
	if (state->m_invert_clk)
		fec_oc_reg_ipr_invert |= FEC_OC_IPR_INVERT_MCLK__M;

	return write16(state, FEC_OC_IPR_INVERT__A, fec_oc_reg_ipr_invert);
}