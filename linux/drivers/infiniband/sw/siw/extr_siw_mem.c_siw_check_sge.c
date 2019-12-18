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
typedef  scalar_t__ u32 ;
struct siw_sge {scalar_t__ length; int lkey; scalar_t__ laddr; } ;
struct siw_mem {int stag; } ;
struct siw_device {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  enum ib_access_flags { ____Placeholder_ib_access_flags } ib_access_flags ;

/* Variables and functions */
 int E_ACCESS_OK ; 
 int E_BASE_BOUNDS ; 
 int E_STAG_INVALID ; 
 int siw_check_mem (struct ib_pd*,struct siw_mem*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  siw_dbg_mem (struct siw_mem*,char*,int) ; 
 int /*<<< orphan*/  siw_dbg_pd (struct ib_pd*,char*,int) ; 
 struct siw_mem* siw_mem_id2obj (struct siw_device*,int) ; 
 int /*<<< orphan*/  siw_mem_put (struct siw_mem*) ; 
 struct siw_device* to_siw_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int siw_check_sge(struct ib_pd *pd, struct siw_sge *sge, struct siw_mem *mem[],
		  enum ib_access_flags perms, u32 off, int len)
{
	struct siw_device *sdev = to_siw_dev(pd->device);
	struct siw_mem *new = NULL;
	int rv = E_ACCESS_OK;

	if (len + off > sge->length) {
		rv = -E_BASE_BOUNDS;
		goto fail;
	}
	if (*mem == NULL) {
		new = siw_mem_id2obj(sdev, sge->lkey >> 8);
		if (unlikely(!new)) {
			siw_dbg_pd(pd, "STag unknown: 0x%08x\n", sge->lkey);
			rv = -E_STAG_INVALID;
			goto fail;
		}
		*mem = new;
	}
	/* Check if user re-registered with different STag key */
	if (unlikely((*mem)->stag != sge->lkey)) {
		siw_dbg_mem((*mem), "STag mismatch: 0x%08x\n", sge->lkey);
		rv = -E_STAG_INVALID;
		goto fail;
	}
	rv = siw_check_mem(pd, *mem, sge->laddr + off, perms, len);
	if (unlikely(rv))
		goto fail;

	return 0;

fail:
	if (new) {
		*mem = NULL;
		siw_mem_put(new);
	}
	return rv;
}