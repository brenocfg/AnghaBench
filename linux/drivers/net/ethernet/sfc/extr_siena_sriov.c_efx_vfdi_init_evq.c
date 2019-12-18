#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {unsigned int index; unsigned int buf_count; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ init_evq; } ;
struct vfdi_req {TYPE_3__ u; } ;
struct TYPE_4__ {struct vfdi_req* addr; } ;
struct siena_vf {unsigned int evq0_count; int /*<<< orphan*/  evq0_addrs; int /*<<< orphan*/  pci_name; TYPE_1__ buf; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  efx_oword_t ;

/* Variables and functions */
 unsigned int EFX_BUFTBL_EVQ_BASE (struct siena_vf*,unsigned int) ; 
 int /*<<< orphan*/  EFX_MAX_VF_EVQ_SIZE ; 
 int /*<<< orphan*/  EFX_POPULATE_OWORD_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int FFE_CZ_TIMER_MODE_DIS ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_BUF_BASE_ID ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_EN ; 
 int /*<<< orphan*/  FRF_AZ_EVQ_SIZE ; 
 int /*<<< orphan*/  FRF_CZ_HOST_NOTIFY_MODE ; 
 int /*<<< orphan*/  FRF_CZ_TIMER_MODE ; 
 int /*<<< orphan*/  FRF_CZ_TIMER_Q_EN ; 
 int /*<<< orphan*/  FR_BZ_EVQ_PTR_TBL ; 
 int /*<<< orphan*/  FR_BZ_TIMER_TBL ; 
 int VFDI_RC_EINVAL ; 
 int VFDI_RC_SUCCESS ; 
 int /*<<< orphan*/  __ffs (unsigned int) ; 
 unsigned int abs_index (struct siena_vf*,unsigned int) ; 
 scalar_t__ bad_buf_count (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ bad_vf_index (struct efx_nic*,unsigned int) ; 
 int /*<<< orphan*/  efx_siena_sriov_bufs (struct efx_nic*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  efx_writeo_table (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int efx_vfdi_init_evq(struct siena_vf *vf)
{
	struct efx_nic *efx = vf->efx;
	struct vfdi_req *req = vf->buf.addr;
	unsigned vf_evq = req->u.init_evq.index;
	unsigned buf_count = req->u.init_evq.buf_count;
	unsigned abs_evq = abs_index(vf, vf_evq);
	unsigned buftbl = EFX_BUFTBL_EVQ_BASE(vf, vf_evq);
	efx_oword_t reg;

	if (bad_vf_index(efx, vf_evq) ||
	    bad_buf_count(buf_count, EFX_MAX_VF_EVQ_SIZE)) {
		if (net_ratelimit())
			netif_err(efx, hw, efx->net_dev,
				  "ERROR: Invalid INIT_EVQ from %s: evq %d bufs %d\n",
				  vf->pci_name, vf_evq, buf_count);
		return VFDI_RC_EINVAL;
	}

	efx_siena_sriov_bufs(efx, buftbl, req->u.init_evq.addr, buf_count);

	EFX_POPULATE_OWORD_3(reg,
			     FRF_CZ_TIMER_Q_EN, 1,
			     FRF_CZ_HOST_NOTIFY_MODE, 0,
			     FRF_CZ_TIMER_MODE, FFE_CZ_TIMER_MODE_DIS);
	efx_writeo_table(efx, &reg, FR_BZ_TIMER_TBL, abs_evq);
	EFX_POPULATE_OWORD_3(reg,
			     FRF_AZ_EVQ_EN, 1,
			     FRF_AZ_EVQ_SIZE, __ffs(buf_count),
			     FRF_AZ_EVQ_BUF_BASE_ID, buftbl);
	efx_writeo_table(efx, &reg, FR_BZ_EVQ_PTR_TBL, abs_evq);

	if (vf_evq == 0) {
		memcpy(vf->evq0_addrs, req->u.init_evq.addr,
		       buf_count * sizeof(u64));
		vf->evq0_count = buf_count;
	}

	return VFDI_RC_SUCCESS;
}