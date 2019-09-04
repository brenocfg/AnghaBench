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
struct emac_regs {int dummy; } ;
struct emac_instance {int /*<<< orphan*/  emacp; int /*<<< orphan*/  cell_index; } ;
struct emac_ethtool_regs_subhdr {int /*<<< orphan*/  version; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC4SYNC_ETHTOOL_REGS_VER ; 
 int /*<<< orphan*/  EMAC4_ETHTOOL_REGS_VER ; 
 int /*<<< orphan*/  EMAC_ETHTOOL_REGS_VER ; 
 int /*<<< orphan*/  EMAC_FTR_EMAC4 ; 
 int /*<<< orphan*/  EMAC_FTR_EMAC4SYNC ; 
 scalar_t__ emac_has_feature (struct emac_instance*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_fromio (struct emac_ethtool_regs_subhdr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *emac_dump_regs(struct emac_instance *dev, void *buf)
{
	struct emac_ethtool_regs_subhdr *hdr = buf;

	hdr->index = dev->cell_index;
	if (emac_has_feature(dev, EMAC_FTR_EMAC4SYNC)) {
		hdr->version = EMAC4SYNC_ETHTOOL_REGS_VER;
	} else if (emac_has_feature(dev, EMAC_FTR_EMAC4)) {
		hdr->version = EMAC4_ETHTOOL_REGS_VER;
	} else {
		hdr->version = EMAC_ETHTOOL_REGS_VER;
	}
	memcpy_fromio(hdr + 1, dev->emacp, sizeof(struct emac_regs));
	return (void *)(hdr + 1) + sizeof(struct emac_regs);
}