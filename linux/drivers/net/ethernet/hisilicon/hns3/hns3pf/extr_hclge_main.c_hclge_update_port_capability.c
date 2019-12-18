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
struct hclge_mac {scalar_t__ media_type; scalar_t__ module_type; int support_autoneg; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Autoneg_BIT ; 
 scalar_t__ HNAE3_MEDIA_TYPE_BACKPLANE ; 
 scalar_t__ HNAE3_MEDIA_TYPE_COPPER ; 
 scalar_t__ HNAE3_MODULE_TYPE_KR ; 
 scalar_t__ HNAE3_MODULE_TYPE_TP ; 
 scalar_t__ HNAE3_MODULE_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  hclge_convert_setting_fec (struct hclge_mac*) ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hclge_update_port_capability(struct hclge_mac *mac)
{
	/* update fec ability by speed */
	hclge_convert_setting_fec(mac);

	/* firmware can not identify back plane type, the media type
	 * read from configuration can help deal it
	 */
	if (mac->media_type == HNAE3_MEDIA_TYPE_BACKPLANE &&
	    mac->module_type == HNAE3_MODULE_TYPE_UNKNOWN)
		mac->module_type = HNAE3_MODULE_TYPE_KR;
	else if (mac->media_type == HNAE3_MEDIA_TYPE_COPPER)
		mac->module_type = HNAE3_MODULE_TYPE_TP;

	if (mac->support_autoneg == true) {
		linkmode_set_bit(ETHTOOL_LINK_MODE_Autoneg_BIT, mac->supported);
		linkmode_copy(mac->advertising, mac->supported);
	} else {
		linkmode_clear_bit(ETHTOOL_LINK_MODE_Autoneg_BIT,
				   mac->supported);
		linkmode_zero(mac->advertising);
	}
}