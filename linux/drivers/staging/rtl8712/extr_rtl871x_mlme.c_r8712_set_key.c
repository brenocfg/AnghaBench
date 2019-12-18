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
typedef  void* u8 ;
struct setkey_parm {int algorithm; int grpkey; void** parmbuf; int cmdsz; int /*<<< orphan*/  list; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  key; void* keyid; } ;
struct security_priv {int AuthAlgrthm; int /*<<< orphan*/ * XGrpKey; TYPE_1__* DefKey; scalar_t__ PrivacyAlgrthm; scalar_t__ XGrpPrivacy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int algorithm; int grpkey; void** parmbuf; int cmdsz; int /*<<< orphan*/  list; scalar_t__ rspsz; int /*<<< orphan*/ * rsp; int /*<<< orphan*/  cmdcode; int /*<<< orphan*/  key; void* keyid; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;
typedef  size_t sint ;
struct TYPE_2__ {int /*<<< orphan*/ * skey; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
#define  _AES_ 131 
 int /*<<< orphan*/  _SetKey_CMD_ ; 
#define  _TKIP_ 130 
#define  _WEP104_ 129 
#define  _WEP40_ 128 
 int /*<<< orphan*/  kfree (struct setkey_parm*) ; 
 struct setkey_parm* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct setkey_parm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct setkey_parm*) ; 

int r8712_set_key(struct _adapter *adapter,
		  struct security_priv *psecuritypriv,
		  sint keyid)
{
	struct cmd_priv *pcmdpriv = &adapter->cmdpriv;
	struct cmd_obj *pcmd;
	struct setkey_parm *psetkeyparm;
	u8 keylen;
	int ret;

	pcmd = kmalloc(sizeof(*pcmd), GFP_ATOMIC);
	if (!pcmd)
		return -ENOMEM;
	psetkeyparm = kzalloc(sizeof(*psetkeyparm), GFP_ATOMIC);
	if (!psetkeyparm) {
		ret = -ENOMEM;
		goto err_free_cmd;
	}
	if (psecuritypriv->AuthAlgrthm == 2) { /* 802.1X */
		psetkeyparm->algorithm =
			 (u8)psecuritypriv->XGrpPrivacy;
	} else { /* WEP */
		psetkeyparm->algorithm =
			 (u8)psecuritypriv->PrivacyAlgrthm;
	}
	psetkeyparm->keyid = (u8)keyid;

	switch (psetkeyparm->algorithm) {
	case _WEP40_:
		keylen = 5;
		memcpy(psetkeyparm->key,
			psecuritypriv->DefKey[keyid].skey, keylen);
		break;
	case _WEP104_:
		keylen = 13;
		memcpy(psetkeyparm->key,
			psecuritypriv->DefKey[keyid].skey, keylen);
		break;
	case _TKIP_:
		if (keyid < 1 || keyid > 2) {
			ret = -EINVAL;
			goto err_free_parm;
		}
		keylen = 16;
		memcpy(psetkeyparm->key,
			&psecuritypriv->XGrpKey[keyid - 1], keylen);
		psetkeyparm->grpkey = 1;
		break;
	case _AES_:
		if (keyid < 1 || keyid > 2) {
			ret = -EINVAL;
			goto err_free_parm;
		}
		keylen = 16;
		memcpy(psetkeyparm->key,
			&psecuritypriv->XGrpKey[keyid - 1], keylen);
		psetkeyparm->grpkey = 1;
		break;
	default:
		ret = -EINVAL;
		goto err_free_parm;
	}
	pcmd->cmdcode = _SetKey_CMD_;
	pcmd->parmbuf = (u8 *)psetkeyparm;
	pcmd->cmdsz =  (sizeof(struct setkey_parm));
	pcmd->rsp = NULL;
	pcmd->rspsz = 0;
	INIT_LIST_HEAD(&pcmd->list);
	r8712_enqueue_cmd(pcmdpriv, pcmd);
	return 0;

err_free_parm:
	kfree(psetkeyparm);
err_free_cmd:
	kfree(pcmd);
	return ret;
}