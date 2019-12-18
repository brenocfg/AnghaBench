#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iw_point {int flags; } ;
union iwreq_data {struct iw_point encoding; } ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {int key_len; int alg; int ext_flags; struct iw_encode_ext* rx_seq; } ;
struct TYPE_3__ {int set_tx; int idx; int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  seq; scalar_t__ alg; } ;
struct TYPE_4__ {TYPE_1__ crypt; } ;
struct ieee_param {TYPE_2__ u; int /*<<< orphan*/  sta_addr; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE_CMD_SET_ENCRYPTION ; 
 int /*<<< orphan*/  IEEE_CRYPT_ALG_NAME_LEN ; 
#define  IW_ENCODE_ALG_AES_CMAC 132 
#define  IW_ENCODE_ALG_CCMP 131 
#define  IW_ENCODE_ALG_NONE 130 
#define  IW_ENCODE_ALG_TKIP 129 
#define  IW_ENCODE_ALG_WEP 128 
 int IW_ENCODE_DISABLED ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 int IW_ENCODE_EXT_RX_SEQ_VALID ; 
 int IW_ENCODE_EXT_SET_TX_KEY ; 
 int /*<<< orphan*/  kfree (struct ieee_param*) ; 
 struct ieee_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct iw_encode_ext*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 int wpa_set_encryption (struct net_device*,struct ieee_param*,int) ; 

__attribute__((used)) static int rtw_wx_set_enc_ext(struct net_device *dev,
			     struct iw_request_info *info,
			     union iwreq_data *wrqu, char *extra)
{
	char *alg_name;
	u32 param_len;
	struct ieee_param *param = NULL;
	struct iw_point *pencoding = &wrqu->encoding;
	struct iw_encode_ext *pext = (struct iw_encode_ext *)extra;
	int ret = 0;

	param_len = sizeof(struct ieee_param) + pext->key_len;
	param = kzalloc(param_len, GFP_KERNEL);
	if (param == NULL)
		return -1;

	param->cmd = IEEE_CMD_SET_ENCRYPTION;
	memset(param->sta_addr, 0xff, ETH_ALEN);


	switch (pext->alg) {
	case IW_ENCODE_ALG_NONE:
		/* todo: remove key */
		/* remove = 1; */
		alg_name = "none";
		break;
	case IW_ENCODE_ALG_WEP:
		alg_name = "WEP";
		break;
	case IW_ENCODE_ALG_TKIP:
		alg_name = "TKIP";
		break;
	case IW_ENCODE_ALG_CCMP:
		alg_name = "CCMP";
		break;
	case IW_ENCODE_ALG_AES_CMAC:
		alg_name = "BIP";
		break;
	default:
		ret = -1;
		goto exit;
	}

	strncpy((char *)param->u.crypt.alg, alg_name, IEEE_CRYPT_ALG_NAME_LEN);

	if (pext->ext_flags & IW_ENCODE_EXT_SET_TX_KEY)
		param->u.crypt.set_tx = 1;

	/* cliW: WEP does not have group key
	 * just not checking GROUP key setting
	 */
	if ((pext->alg != IW_ENCODE_ALG_WEP) &&
		((pext->ext_flags & IW_ENCODE_EXT_GROUP_KEY)
		|| (pext->ext_flags & IW_ENCODE_ALG_AES_CMAC)))	{
		param->u.crypt.set_tx = 0;
	}

	param->u.crypt.idx = (pencoding->flags&0x00FF) -1 ;

	if (pext->ext_flags & IW_ENCODE_EXT_RX_SEQ_VALID)
		memcpy(param->u.crypt.seq, pext->rx_seq, 8);

	if (pext->key_len) {
		param->u.crypt.key_len = pext->key_len;
		/* memcpy(param + 1, pext + 1, pext->key_len); */
		memcpy(param->u.crypt.key, pext + 1, pext->key_len);
	}

	if (pencoding->flags & IW_ENCODE_DISABLED) {
		/* todo: remove key */
		/* remove = 1; */
	}

	ret =  wpa_set_encryption(dev, param, param_len);

exit:
	kfree(param);

	return ret;
}