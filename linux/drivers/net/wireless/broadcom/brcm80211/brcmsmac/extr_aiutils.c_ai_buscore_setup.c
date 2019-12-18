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
struct TYPE_6__ {int pmucaps; int pmurev; void* cccaps; int /*<<< orphan*/  ccrev; } ;
struct si_info {TYPE_3__ pub; void* chipst; } ;
struct TYPE_4__ {int /*<<< orphan*/  rev; } ;
struct bcma_device {TYPE_1__ id; TYPE_2__* bus; } ;
struct TYPE_5__ {scalar_t__ nr_cores; } ;

/* Variables and functions */
 int CC_CAP_PMU ; 
 int /*<<< orphan*/  CHIPCREGOFFS (int /*<<< orphan*/ ) ; 
 int PCAP_REV_MASK ; 
 int ai_get_cccaps (TYPE_3__*) ; 
 void* bcma_read32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capabilities ; 
 int /*<<< orphan*/  chipstatus ; 
 int /*<<< orphan*/  pmucapabilities ; 

__attribute__((used)) static bool
ai_buscore_setup(struct si_info *sii, struct bcma_device *cc)
{
	/* no cores found, bail out */
	if (cc->bus->nr_cores == 0)
		return false;

	/* get chipcommon rev */
	sii->pub.ccrev = cc->id.rev;

	/* get chipcommon chipstatus */
	sii->chipst = bcma_read32(cc, CHIPCREGOFFS(chipstatus));

	/* get chipcommon capabilites */
	sii->pub.cccaps = bcma_read32(cc, CHIPCREGOFFS(capabilities));

	/* get pmu rev and caps */
	if (ai_get_cccaps(&sii->pub) & CC_CAP_PMU) {
		sii->pub.pmucaps = bcma_read32(cc,
					       CHIPCREGOFFS(pmucapabilities));
		sii->pub.pmurev = sii->pub.pmucaps & PCAP_REV_MASK;
	}

	return true;
}