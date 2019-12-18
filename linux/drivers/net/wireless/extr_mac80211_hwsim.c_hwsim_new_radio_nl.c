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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct hwsim_new_radio_params {int reg_strict; int p2p_device; int channels; int destroy_on_close; int no_vif; int use_chanctx; int iftypes; size_t n_ciphers; char const* hwname; void* ciphers; void* perm_addr; int /*<<< orphan*/  regd; void* reg_alpha2; int /*<<< orphan*/  member_0; } ;
struct genl_info {int* attrs; int /*<<< orphan*/  extack; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int CFG80211_MAX_NUM_DIFFERENT_CHANNELS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENL_SET_ERR_MSG (struct genl_info*,char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t HWSIM_ATTR_CHANNELS ; 
 size_t HWSIM_ATTR_CIPHER_SUPPORT ; 
 size_t HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE ; 
 size_t HWSIM_ATTR_IFTYPE_SUPPORT ; 
 size_t HWSIM_ATTR_NO_VIF ; 
 size_t HWSIM_ATTR_PERM_ADDR ; 
 size_t HWSIM_ATTR_RADIO_NAME ; 
 size_t HWSIM_ATTR_REG_CUSTOM_REG ; 
 size_t HWSIM_ATTR_REG_HINT_ALPHA2 ; 
 size_t HWSIM_ATTR_REG_STRICT_REG ; 
 size_t HWSIM_ATTR_SUPPORT_P2P_DEVICE ; 
 size_t HWSIM_ATTR_USE_CHANCTX ; 
 int HWSIM_IFTYPE_SUPPORT_MASK ; 
 int /*<<< orphan*/  NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  NL_SET_BAD_ATTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_ATTR (int /*<<< orphan*/ ,int,char*) ; 
 size_t array_index_nospec (size_t,size_t) ; 
 int channels ; 
 int /*<<< orphan*/ * hwsim_ciphers ; 
 int /*<<< orphan*/  hwsim_known_ciphers (void*,size_t) ; 
 int /*<<< orphan*/ * hwsim_world_regdom_custom ; 
 int /*<<< orphan*/  is_valid_ether_addr (void*) ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,size_t,char*) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int mac80211_hwsim_new_radio (struct genl_info*,struct hwsim_new_radio_params*) ; 
 void* nla_data (int) ; 
 void* nla_get_u32 (int) ; 
 size_t nla_len (int) ; 

__attribute__((used)) static int hwsim_new_radio_nl(struct sk_buff *msg, struct genl_info *info)
{
	struct hwsim_new_radio_params param = { 0 };
	const char *hwname = NULL;
	int ret;

	param.reg_strict = info->attrs[HWSIM_ATTR_REG_STRICT_REG];
	param.p2p_device = info->attrs[HWSIM_ATTR_SUPPORT_P2P_DEVICE];
	param.channels = channels;
	param.destroy_on_close =
		info->attrs[HWSIM_ATTR_DESTROY_RADIO_ON_CLOSE];

	if (info->attrs[HWSIM_ATTR_CHANNELS])
		param.channels = nla_get_u32(info->attrs[HWSIM_ATTR_CHANNELS]);

	if (param.channels < 1) {
		GENL_SET_ERR_MSG(info, "must have at least one channel");
		return -EINVAL;
	}

	if (param.channels > CFG80211_MAX_NUM_DIFFERENT_CHANNELS) {
		GENL_SET_ERR_MSG(info, "too many channels specified");
		return -EINVAL;
	}

	if (info->attrs[HWSIM_ATTR_NO_VIF])
		param.no_vif = true;

	if (info->attrs[HWSIM_ATTR_USE_CHANCTX])
		param.use_chanctx = true;
	else
		param.use_chanctx = (param.channels > 1);

	if (info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2])
		param.reg_alpha2 =
			nla_data(info->attrs[HWSIM_ATTR_REG_HINT_ALPHA2]);

	if (info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]) {
		u32 idx = nla_get_u32(info->attrs[HWSIM_ATTR_REG_CUSTOM_REG]);

		if (idx >= ARRAY_SIZE(hwsim_world_regdom_custom))
			return -EINVAL;

		idx = array_index_nospec(idx,
					 ARRAY_SIZE(hwsim_world_regdom_custom));
		param.regd = hwsim_world_regdom_custom[idx];
	}

	if (info->attrs[HWSIM_ATTR_PERM_ADDR]) {
		if (!is_valid_ether_addr(
				nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]))) {
			GENL_SET_ERR_MSG(info,"MAC is no valid source addr");
			NL_SET_BAD_ATTR(info->extack,
					info->attrs[HWSIM_ATTR_PERM_ADDR]);
			return -EINVAL;
		}

		param.perm_addr = nla_data(info->attrs[HWSIM_ATTR_PERM_ADDR]);
	}

	if (info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT]) {
		param.iftypes =
			nla_get_u32(info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT]);

		if (param.iftypes & ~HWSIM_IFTYPE_SUPPORT_MASK) {
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_IFTYPE_SUPPORT],
					    "cannot support more iftypes than kernel");
			return -EINVAL;
		}
	} else {
		param.iftypes = HWSIM_IFTYPE_SUPPORT_MASK;
	}

	/* ensure both flag and iftype support is honored */
	if (param.p2p_device ||
	    param.iftypes & BIT(NL80211_IFTYPE_P2P_DEVICE)) {
		param.iftypes |= BIT(NL80211_IFTYPE_P2P_DEVICE);
		param.p2p_device = true;
	}

	if (info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]) {
		u32 len = nla_len(info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]);

		param.ciphers =
			nla_data(info->attrs[HWSIM_ATTR_CIPHER_SUPPORT]);

		if (len % sizeof(u32)) {
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "bad cipher list length");
			return -EINVAL;
		}

		param.n_ciphers = len / sizeof(u32);

		if (param.n_ciphers > ARRAY_SIZE(hwsim_ciphers)) {
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "too many ciphers specified");
			return -EINVAL;
		}

		if (!hwsim_known_ciphers(param.ciphers, param.n_ciphers)) {
			NL_SET_ERR_MSG_ATTR(info->extack,
					    info->attrs[HWSIM_ATTR_CIPHER_SUPPORT],
					    "unsupported ciphers specified");
			return -EINVAL;
		}
	}

	if (info->attrs[HWSIM_ATTR_RADIO_NAME]) {
		hwname = kasprintf(GFP_KERNEL, "%.*s",
				   nla_len(info->attrs[HWSIM_ATTR_RADIO_NAME]),
				   (char *)nla_data(info->attrs[HWSIM_ATTR_RADIO_NAME]));
		if (!hwname)
			return -ENOMEM;
		param.hwname = hwname;
	}

	ret = mac80211_hwsim_new_radio(info, &param);
	kfree(hwname);
	return ret;
}