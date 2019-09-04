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
typedef  int u32 ;
struct skl_wrpll_params {int kdiv; int pdiv; int qdiv_ratio; int qdiv_mode; int dco_integer; int dco_fraction; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int div_u64 (int,int) ; 

__attribute__((used)) static void cnl_wrpll_params_populate(struct skl_wrpll_params *params,
				      u32 dco_freq, u32 ref_freq,
				      int pdiv, int qdiv, int kdiv)
{
	u32 dco;

	switch (kdiv) {
	case 1:
		params->kdiv = 1;
		break;
	case 2:
		params->kdiv = 2;
		break;
	case 3:
		params->kdiv = 4;
		break;
	default:
		WARN(1, "Incorrect KDiv\n");
	}

	switch (pdiv) {
	case 2:
		params->pdiv = 1;
		break;
	case 3:
		params->pdiv = 2;
		break;
	case 5:
		params->pdiv = 4;
		break;
	case 7:
		params->pdiv = 8;
		break;
	default:
		WARN(1, "Incorrect PDiv\n");
	}

	WARN_ON(kdiv != 2 && qdiv != 1);

	params->qdiv_ratio = qdiv;
	params->qdiv_mode = (qdiv == 1) ? 0 : 1;

	dco = div_u64((u64)dco_freq << 15, ref_freq);

	params->dco_integer = dco >> 15;
	params->dco_fraction = dco & 0x7fff;
}