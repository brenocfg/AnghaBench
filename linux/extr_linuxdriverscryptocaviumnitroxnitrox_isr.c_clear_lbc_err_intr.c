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
struct TYPE_2__ {scalar_t__ rd_dat_len_mismatch_err; scalar_t__ pref_dat_len_mismatch_err; scalar_t__ cam_soft_err; scalar_t__ dma_rd_err; } ;
union lbc_int {void* value; TYPE_1__ s; } ;
typedef  void* u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 void* EFL_CORE_VF_ERR_INT0X (int) ; 
 void* EFL_CORE_VF_ERR_INT1X (int) ; 
 void* LBC_ELM_VF1_64_INT ; 
 void* LBC_ELM_VF65_128_INT ; 
 void* LBC_INT ; 
 void* LBC_PLM_VF1_64_INT ; 
 void* LBC_PLM_VF65_128_INT ; 
 int NR_CLUSTERS ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  invalidate_lbc (struct nitrox_device*) ; 
 void* nitrox_read_csr (struct nitrox_device*,void*) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,void*,void*) ; 

__attribute__((used)) static void clear_lbc_err_intr(struct nitrox_device *ndev)
{
	union lbc_int lbc_int;
	u64 value, offset;
	int i;

	lbc_int.value = nitrox_read_csr(ndev, LBC_INT);
	dev_err_ratelimited(DEV(ndev), "LBC_INT  0x%016llx\n", lbc_int.value);

	if (lbc_int.s.dma_rd_err) {
		for (i = 0; i < NR_CLUSTERS; i++) {
			offset = EFL_CORE_VF_ERR_INT0X(i);
			value = nitrox_read_csr(ndev, offset);
			nitrox_write_csr(ndev, offset, value);
			offset = EFL_CORE_VF_ERR_INT1X(i);
			value = nitrox_read_csr(ndev, offset);
			nitrox_write_csr(ndev, offset, value);
		}
	}

	if (lbc_int.s.cam_soft_err) {
		dev_err_ratelimited(DEV(ndev), "CAM_SOFT_ERR, invalidating LBC\n");
		invalidate_lbc(ndev);
	}

	if (lbc_int.s.pref_dat_len_mismatch_err) {
		offset = LBC_PLM_VF1_64_INT;
		value = nitrox_read_csr(ndev, offset);
		nitrox_write_csr(ndev, offset, value);
		offset = LBC_PLM_VF65_128_INT;
		value = nitrox_read_csr(ndev, offset);
		nitrox_write_csr(ndev, offset, value);
	}

	if (lbc_int.s.rd_dat_len_mismatch_err) {
		offset = LBC_ELM_VF1_64_INT;
		value = nitrox_read_csr(ndev, offset);
		nitrox_write_csr(ndev, offset, value);
		offset = LBC_ELM_VF65_128_INT;
		value = nitrox_read_csr(ndev, offset);
		nitrox_write_csr(ndev, offset, value);
	}
	nitrox_write_csr(ndev, LBC_INT, lbc_int.value);
}