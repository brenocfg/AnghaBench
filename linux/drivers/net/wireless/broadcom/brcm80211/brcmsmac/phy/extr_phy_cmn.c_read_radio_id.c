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
typedef  int u32 ;
struct brcms_phy {scalar_t__ phy_wreg; int /*<<< orphan*/  d11core; TYPE_1__* sh; } ;
struct TYPE_2__ {int /*<<< orphan*/  corerev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 scalar_t__ D11REV_GE (int /*<<< orphan*/ ,int) ; 
 int RADIO_IDCODE ; 
 scalar_t__ bcma_read16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_wflush16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy4waddr ; 
 int /*<<< orphan*/  phy4wdatahi ; 
 int /*<<< orphan*/  phy4wdatalo ; 
 int /*<<< orphan*/  radioregaddr ; 
 int /*<<< orphan*/  radioregdata ; 

__attribute__((used)) static u32 read_radio_id(struct brcms_phy *pi)
{
	u32 id;

	if (D11REV_GE(pi->sh->corerev, 24)) {
		u32 b0, b1, b2;

		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 0);
		b0 = (u32) bcma_read16(pi->d11core, D11REGOFFS(radioregdata));
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 1);
		b1 = (u32) bcma_read16(pi->d11core, D11REGOFFS(radioregdata));
		bcma_wflush16(pi->d11core, D11REGOFFS(radioregaddr), 2);
		b2 = (u32) bcma_read16(pi->d11core, D11REGOFFS(radioregdata));

		id = ((b0 & 0xf) << 28) | (((b2 << 8) | b1) << 12) | ((b0 >> 4)
								      & 0xf);
	} else {
		bcma_wflush16(pi->d11core, D11REGOFFS(phy4waddr), RADIO_IDCODE);
		id = (u32) bcma_read16(pi->d11core, D11REGOFFS(phy4wdatalo));
		id |= (u32) bcma_read16(pi->d11core,
					D11REGOFFS(phy4wdatahi)) << 16;
	}
	pi->phy_wreg = 0;
	return id;
}