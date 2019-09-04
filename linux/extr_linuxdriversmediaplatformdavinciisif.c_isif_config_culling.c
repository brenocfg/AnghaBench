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
struct isif_cul {int hcpat_even; int hcpat_odd; int vcpat; int en_lpf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CULH ; 
 int CULL_PAT_EVEN_LINE_SHIFT ; 
 int /*<<< orphan*/  CULV ; 
 int ISIF_LPF_MASK ; 
 int ISIF_LPF_SHIFT ; 
 int /*<<< orphan*/  MODESET ; 
 int /*<<< orphan*/  reg_modify (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isif_config_culling(struct isif_cul *cul)
{
	u32 val;

	/* Horizontal pattern */
	val = (cul->hcpat_even << CULL_PAT_EVEN_LINE_SHIFT) | cul->hcpat_odd;
	regw(val, CULH);

	/* vertical pattern */
	regw(cul->vcpat, CULV);

	/* LPF */
	reg_modify(ISIF_LPF_MASK << ISIF_LPF_SHIFT,
		  cul->en_lpf << ISIF_LPF_SHIFT, MODESET);
}