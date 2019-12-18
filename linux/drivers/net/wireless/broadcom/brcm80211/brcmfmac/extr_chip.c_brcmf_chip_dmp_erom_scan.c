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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct brcmf_core {scalar_t__ rev; } ;
struct brcmf_chip_priv {int /*<<< orphan*/  ctx; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* read32 ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ BCMA_CORE_GCI ; 
 scalar_t__ BCMA_CORE_PMU ; 
 int /*<<< orphan*/  CORE_CC_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ DMP_COMP_NUM_MPORT ; 
 scalar_t__ DMP_COMP_NUM_MPORT_S ; 
 scalar_t__ DMP_COMP_NUM_MWRAP ; 
 scalar_t__ DMP_COMP_NUM_MWRAP_S ; 
 scalar_t__ DMP_COMP_NUM_SPORT ; 
 scalar_t__ DMP_COMP_NUM_SPORT_S ; 
 scalar_t__ DMP_COMP_NUM_SWRAP ; 
 scalar_t__ DMP_COMP_NUM_SWRAP_S ; 
 scalar_t__ DMP_COMP_PARTNUM ; 
 scalar_t__ DMP_COMP_PARTNUM_S ; 
 scalar_t__ DMP_COMP_REVISION ; 
 scalar_t__ DMP_COMP_REVISION_S ; 
 scalar_t__ DMP_DESC_COMPONENT ; 
 scalar_t__ DMP_DESC_EMPTY ; 
 scalar_t__ DMP_DESC_EOT ; 
 scalar_t__ DMP_DESC_TYPE_MSK ; 
 scalar_t__ DMP_DESC_VALID ; 
 int EFAULT ; 
 scalar_t__ IS_ERR (struct brcmf_core*) ; 
 int PTR_ERR (struct brcmf_core*) ; 
 int /*<<< orphan*/  SI_ENUM_BASE ; 
 scalar_t__ WARN_ON (int) ; 
 struct brcmf_core* brcmf_chip_add_core (struct brcmf_chip_priv*,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ brcmf_chip_dmp_get_desc (struct brcmf_chip_priv*,scalar_t__*,scalar_t__*) ; 
 int brcmf_chip_dmp_get_regaddr (struct brcmf_chip_priv*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  eromptr ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int brcmf_chip_dmp_erom_scan(struct brcmf_chip_priv *ci)
{
	struct brcmf_core *core;
	u32 eromaddr;
	u8 desc_type = 0;
	u32 val;
	u16 id;
	u8 nmp, nsp, nmw, nsw, rev;
	u32 base, wrap;
	int err;

	eromaddr = ci->ops->read32(ci->ctx, CORE_CC_REG(SI_ENUM_BASE, eromptr));

	while (desc_type != DMP_DESC_EOT) {
		val = brcmf_chip_dmp_get_desc(ci, &eromaddr, &desc_type);
		if (!(val & DMP_DESC_VALID))
			continue;

		if (desc_type == DMP_DESC_EMPTY)
			continue;

		/* need a component descriptor */
		if (desc_type != DMP_DESC_COMPONENT)
			continue;

		id = (val & DMP_COMP_PARTNUM) >> DMP_COMP_PARTNUM_S;

		/* next descriptor must be component as well */
		val = brcmf_chip_dmp_get_desc(ci, &eromaddr, &desc_type);
		if (WARN_ON((val & DMP_DESC_TYPE_MSK) != DMP_DESC_COMPONENT))
			return -EFAULT;

		/* only look at cores with master port(s) */
		nmp = (val & DMP_COMP_NUM_MPORT) >> DMP_COMP_NUM_MPORT_S;
		nsp = (val & DMP_COMP_NUM_SPORT) >> DMP_COMP_NUM_SPORT_S;
		nmw = (val & DMP_COMP_NUM_MWRAP) >> DMP_COMP_NUM_MWRAP_S;
		nsw = (val & DMP_COMP_NUM_SWRAP) >> DMP_COMP_NUM_SWRAP_S;
		rev = (val & DMP_COMP_REVISION) >> DMP_COMP_REVISION_S;

		/* need core with ports */
		if (nmw + nsw == 0 &&
		    id != BCMA_CORE_PMU &&
		    id != BCMA_CORE_GCI)
			continue;

		/* try to obtain register address info */
		err = brcmf_chip_dmp_get_regaddr(ci, &eromaddr, &base, &wrap);
		if (err)
			continue;

		/* finally a core to be added */
		core = brcmf_chip_add_core(ci, id, base, wrap);
		if (IS_ERR(core))
			return PTR_ERR(core);

		core->rev = rev;
	}

	return 0;
}