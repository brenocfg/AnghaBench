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
struct nfp_rtsym {int dummy; } ;
struct nfp_pf {int dummy; } ;

/* Variables and functions */
 unsigned int NFP_NET_MAX_RX_RINGS ; 
 struct nfp_rtsym const* nfp_abm_ctrl_find_rtsym (struct nfp_pf*,char const*,unsigned int) ; 

__attribute__((used)) static const struct nfp_rtsym *
nfp_abm_ctrl_find_q_rtsym(struct nfp_pf *pf, const char *name,
			  unsigned int size)
{
	return nfp_abm_ctrl_find_rtsym(pf, name, size * NFP_NET_MAX_RX_RINGS);
}