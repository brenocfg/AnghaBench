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
typedef  int u8 ;
struct setkey_parm {int keyid; int algorithm; int set_tx; int /*<<< orphan*/ * key; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int* parmbuf; int cmdsz; int /*<<< orphan*/  list; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; } ;
struct TYPE_2__ {int /*<<< orphan*/  key_mask; } ;
struct adapter {TYPE_1__ securitypriv; struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  _AES_ 132 
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _SetKey_CMD_ ; 
#define  _TKIP_ 131 
#define  _TKIP_WTMIC_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 scalar_t__ is_wep_enc (int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 void* rtw_zmalloc (int) ; 

__attribute__((used)) static int rtw_ap_set_key(
	struct adapter *padapter,
	u8 *key,
	u8 alg,
	int keyid,
	u8 set_tx
)
{
	u8 keylen;
	struct cmd_obj *pcmd;
	struct setkey_parm *psetkeyparm;
	struct cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	int res = _SUCCESS;

	/* DBG_871X("%s\n", __func__); */

	pcmd = rtw_zmalloc(sizeof(struct cmd_obj));
	if (pcmd == NULL) {
		res = _FAIL;
		goto exit;
	}
	psetkeyparm = rtw_zmalloc(sizeof(struct setkey_parm));
	if (psetkeyparm == NULL) {
		kfree((unsigned char *)pcmd);
		res = _FAIL;
		goto exit;
	}

	psetkeyparm->keyid = (u8)keyid;
	if (is_wep_enc(alg))
		padapter->securitypriv.key_mask |= BIT(psetkeyparm->keyid);

	psetkeyparm->algorithm = alg;

	psetkeyparm->set_tx = set_tx;

	switch (alg) {
	case _WEP40_:
		keylen = 5;
		break;
	case _WEP104_:
		keylen = 13;
		break;
	case _TKIP_:
	case _TKIP_WTMIC_:
	case _AES_:
	default:
		keylen = 16;
	}

	memcpy(&(psetkeyparm->key[0]), key, keylen);

	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  (sizeof(struct setkey_parm));
	pcmd->rsp = NULL;
	pcmd->rspsz = 0;

	INIT_LIST_HEAD(&pcmd->list);

	res = rtw_enqueue_cmd(pcmdpriv, pcmd);

exit:

	return res;
}