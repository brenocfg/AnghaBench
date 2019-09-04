#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct nfp_rtsym {int dummy; } ;
struct nfp_abm_link {TYPE_1__* vnic; } ;
struct TYPE_2__ {unsigned int max_rx_rings; } ;

/* Variables and functions */
 int nfp_abm_ctrl_stat (struct nfp_abm_link*,struct nfp_rtsym const*,unsigned int,unsigned int,unsigned int,int,scalar_t__*) ; 

__attribute__((used)) static int
nfp_abm_ctrl_stat_all(struct nfp_abm_link *alink, const struct nfp_rtsym *sym,
		      unsigned int stride, unsigned int offset, bool is_u64,
		      u64 *res)
{
	u64 val, sum = 0;
	unsigned int i;
	int err;

	for (i = 0; i < alink->vnic->max_rx_rings; i++) {
		err = nfp_abm_ctrl_stat(alink, sym, stride, offset, i,
					is_u64, &val);
		if (err)
			return err;
		sum += val;
	}

	*res = sum;
	return 0;
}