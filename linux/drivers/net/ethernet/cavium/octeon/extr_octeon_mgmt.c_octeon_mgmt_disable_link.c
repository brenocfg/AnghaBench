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
struct TYPE_2__ {int tx_idle; int rx_idle; scalar_t__ rx_en; scalar_t__ tx_en; scalar_t__ en; } ;
union cvmx_agl_gmx_prtx_cfg {TYPE_1__ s; void* u64; } ;
struct octeon_mgmt {scalar_t__ agl; } ;

/* Variables and functions */
 scalar_t__ AGL_GMX_PRT_CFG ; 
 int /*<<< orphan*/  OCTEON_CN6XXX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 void* cvmx_read_csr (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_write_csr (scalar_t__,void*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void octeon_mgmt_disable_link(struct octeon_mgmt *p)
{
	union cvmx_agl_gmx_prtx_cfg prtx_cfg;

	/* Disable GMX before we make any changes. */
	prtx_cfg.u64 = cvmx_read_csr(p->agl + AGL_GMX_PRT_CFG);
	prtx_cfg.s.en = 0;
	prtx_cfg.s.tx_en = 0;
	prtx_cfg.s.rx_en = 0;
	cvmx_write_csr(p->agl + AGL_GMX_PRT_CFG, prtx_cfg.u64);

	if (OCTEON_IS_MODEL(OCTEON_CN6XXX)) {
		int i;
		for (i = 0; i < 10; i++) {
			prtx_cfg.u64 = cvmx_read_csr(p->agl + AGL_GMX_PRT_CFG);
			if (prtx_cfg.s.tx_idle == 1 || prtx_cfg.s.rx_idle == 1)
				break;
			mdelay(1);
			i++;
		}
	}
}