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
typedef  int /*<<< orphan*/  u32 ;
struct its_node {int flags; int /*<<< orphan*/  device_ids; struct its_baser* tables; } ;
struct its_baser {int val; int /*<<< orphan*/  psz; } ;

/* Variables and functions */
 int GITS_BASER_CACHEABILITY_MASK ; 
 int GITS_BASER_InnerShareable ; 
 int GITS_BASER_NR_REGS ; 
 int GITS_BASER_RaWaWb ; 
 int GITS_BASER_SHAREABILITY_MASK ; 
 int GITS_BASER_TYPE (int) ; 
#define  GITS_BASER_TYPE_DEVICE 130 
#define  GITS_BASER_TYPE_NONE 129 
#define  GITS_BASER_TYPE_VCPU 128 
 int GITS_BASER_nCnB ; 
 int ITS_FLAGS_WORKAROUND_CAVIUM_22375 ; 
 int /*<<< orphan*/  ITS_MAX_VPEID_BITS ; 
 int /*<<< orphan*/  SZ_64K ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  its_free_tables (struct its_node*) ; 
 int its_parse_indirect_baser (struct its_node*,struct its_baser*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int its_read_baser (struct its_node*,struct its_baser*) ; 
 int its_setup_baser (struct its_node*,struct its_baser*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int its_alloc_tables(struct its_node *its)
{
	u64 shr = GITS_BASER_InnerShareable;
	u64 cache = GITS_BASER_RaWaWb;
	u32 psz = SZ_64K;
	int err, i;

	if (its->flags & ITS_FLAGS_WORKAROUND_CAVIUM_22375)
		/* erratum 24313: ignore memory access type */
		cache = GITS_BASER_nCnB;

	for (i = 0; i < GITS_BASER_NR_REGS; i++) {
		struct its_baser *baser = its->tables + i;
		u64 val = its_read_baser(its, baser);
		u64 type = GITS_BASER_TYPE(val);
		u32 order = get_order(psz);
		bool indirect = false;

		switch (type) {
		case GITS_BASER_TYPE_NONE:
			continue;

		case GITS_BASER_TYPE_DEVICE:
			indirect = its_parse_indirect_baser(its, baser,
							    psz, &order,
							    its->device_ids);
			break;

		case GITS_BASER_TYPE_VCPU:
			indirect = its_parse_indirect_baser(its, baser,
							    psz, &order,
							    ITS_MAX_VPEID_BITS);
			break;
		}

		err = its_setup_baser(its, baser, cache, shr, psz, order, indirect);
		if (err < 0) {
			its_free_tables(its);
			return err;
		}

		/* Update settings which will be used for next BASERn */
		psz = baser->psz;
		cache = baser->val & GITS_BASER_CACHEABILITY_MASK;
		shr = baser->val & GITS_BASER_SHAREABILITY_MASK;
	}

	return 0;
}