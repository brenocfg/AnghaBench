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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  ioc; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_1__ bfa; } ;
struct bfa_bsg_debug_s {scalar_t__ bufsz; scalar_t__ offset; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 scalar_t__ BFA_DEBUG_FW_CORE_CHUNK_SZ ; 
 int /*<<< orphan*/  BFA_STATUS_EINVAL ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_VERSION_FAIL ; 
 int /*<<< orphan*/  IS_ALIGNED (scalar_t__,int) ; 
 int /*<<< orphan*/  bfa_ioc_debug_fwcore (int /*<<< orphan*/ *,void*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,scalar_t__) ; 
 scalar_t__ bfad_chk_iocmd_sz (unsigned int,int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_debug_fw_core(struct bfad_s *bfad, void *cmd,
			unsigned int payload_len)
{
	struct bfa_bsg_debug_s *iocmd = (struct bfa_bsg_debug_s *)cmd;
	void	*iocmd_bufptr;
	unsigned long	flags;
	u32 offset;

	if (bfad_chk_iocmd_sz(payload_len, sizeof(struct bfa_bsg_debug_s),
			BFA_DEBUG_FW_CORE_CHUNK_SZ) != BFA_STATUS_OK) {
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		return 0;
	}

	if (iocmd->bufsz < BFA_DEBUG_FW_CORE_CHUNK_SZ ||
			!IS_ALIGNED(iocmd->bufsz, sizeof(u16)) ||
			!IS_ALIGNED(iocmd->offset, sizeof(u32))) {
		bfa_trc(bfad, BFA_DEBUG_FW_CORE_CHUNK_SZ);
		iocmd->status = BFA_STATUS_EINVAL;
		goto out;
	}

	iocmd_bufptr = (char *)iocmd + sizeof(struct bfa_bsg_debug_s);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	offset = iocmd->offset;
	iocmd->status = bfa_ioc_debug_fwcore(&bfad->bfa.ioc, iocmd_bufptr,
				&offset, &iocmd->bufsz);
	iocmd->offset = offset;
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
out:
	return 0;
}