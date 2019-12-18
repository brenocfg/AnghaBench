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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct wmi {TYPE_1__* parent_dev; } ;
struct reg_dmn_pair_mapping {int /*<<< orphan*/  reg_domain; } ;
struct country_code_to_enum_rd {char* isoName; } ;
struct ath6kl_wmi_regdomain {int /*<<< orphan*/  reg_code; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; scalar_t__ wiphy_registered; } ;

/* Variables and functions */
 int ATH6KL_COUNTRY_RD_SHIFT ; 
 int /*<<< orphan*/  ATH6KL_DBG_WMI ; 
 int COUNTRY_ERD_FLAG ; 
 int WORLD_SKU_MASK ; 
 int WORLD_SKU_PREFIX ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,char,...) ; 
 struct reg_dmn_pair_mapping* ath6kl_get_regpair (int) ; 
 struct country_code_to_enum_rd* ath6kl_regd_find_country (int) ; 
 struct country_code_to_enum_rd* ath6kl_regd_find_country_by_rd (int) ; 
 int /*<<< orphan*/  ath6kl_warn (char*,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulatory_hint (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ath6kl_wmi_regdomain_event(struct wmi *wmi, u8 *datap, int len)
{
	struct ath6kl_wmi_regdomain *ev;
	struct country_code_to_enum_rd *country = NULL;
	struct reg_dmn_pair_mapping *regpair = NULL;
	char alpha2[2];
	u32 reg_code;

	ev = (struct ath6kl_wmi_regdomain *) datap;
	reg_code = le32_to_cpu(ev->reg_code);

	if ((reg_code >> ATH6KL_COUNTRY_RD_SHIFT) & COUNTRY_ERD_FLAG) {
		country = ath6kl_regd_find_country((u16) reg_code);
	} else if (!(((u16) reg_code & WORLD_SKU_MASK) == WORLD_SKU_PREFIX)) {
		regpair = ath6kl_get_regpair((u16) reg_code);
		country = ath6kl_regd_find_country_by_rd((u16) reg_code);
		if (regpair)
			ath6kl_dbg(ATH6KL_DBG_WMI, "Regpair used: 0x%0x\n",
				   regpair->reg_domain);
		else
			ath6kl_warn("Regpair not found reg_code 0x%0x\n",
				    reg_code);
	}

	if (country && wmi->parent_dev->wiphy_registered) {
		alpha2[0] = country->isoName[0];
		alpha2[1] = country->isoName[1];

		regulatory_hint(wmi->parent_dev->wiphy, alpha2);

		ath6kl_dbg(ATH6KL_DBG_WMI, "Country alpha2 being used: %c%c\n",
			   alpha2[0], alpha2[1]);
	}
}