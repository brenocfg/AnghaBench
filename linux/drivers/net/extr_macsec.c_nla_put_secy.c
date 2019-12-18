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
typedef  int /*<<< orphan*/  u64 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct macsec_tx_sc {scalar_t__ encoding_sa; scalar_t__ scb; scalar_t__ end_station; scalar_t__ send_sci; scalar_t__ encrypt; } ;
struct macsec_secy {int key_len; int /*<<< orphan*/  replay_window; scalar_t__ replay_protect; scalar_t__ validate_frames; scalar_t__ protect_frames; scalar_t__ operational; scalar_t__ icv_len; int /*<<< orphan*/  sci; struct macsec_tx_sc tx_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACSEC_ATTR_SECY ; 
 int /*<<< orphan*/  MACSEC_CIPHER_ID_GCM_AES_256 ; 
 int /*<<< orphan*/  MACSEC_DEFAULT_CIPHER_ID ; 
#define  MACSEC_GCM_AES_128_SAK_LEN 129 
#define  MACSEC_GCM_AES_256_SAK_LEN 128 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_CIPHER_SUITE ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_ENCODING_SA ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_ENCRYPT ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_ES ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_ICV_LEN ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_INC_SCI ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_OPER ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_PAD ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_PROTECT ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_REPLAY ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_SCB ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_SCI ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_VALIDATE ; 
 int /*<<< orphan*/  MACSEC_SECY_ATTR_WINDOW ; 
 int /*<<< orphan*/  nla_nest_cancel (struct sk_buff*,struct nlattr*) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_sci (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u64_64bit (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int nla_put_secy(struct macsec_secy *secy, struct sk_buff *skb)
{
	struct macsec_tx_sc *tx_sc = &secy->tx_sc;
	struct nlattr *secy_nest = nla_nest_start_noflag(skb,
							 MACSEC_ATTR_SECY);
	u64 csid;

	if (!secy_nest)
		return 1;

	switch (secy->key_len) {
	case MACSEC_GCM_AES_128_SAK_LEN:
		csid = MACSEC_DEFAULT_CIPHER_ID;
		break;
	case MACSEC_GCM_AES_256_SAK_LEN:
		csid = MACSEC_CIPHER_ID_GCM_AES_256;
		break;
	default:
		goto cancel;
	}

	if (nla_put_sci(skb, MACSEC_SECY_ATTR_SCI, secy->sci,
			MACSEC_SECY_ATTR_PAD) ||
	    nla_put_u64_64bit(skb, MACSEC_SECY_ATTR_CIPHER_SUITE,
			      csid, MACSEC_SECY_ATTR_PAD) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ICV_LEN, secy->icv_len) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_OPER, secy->operational) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_PROTECT, secy->protect_frames) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_REPLAY, secy->replay_protect) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_VALIDATE, secy->validate_frames) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ENCRYPT, tx_sc->encrypt) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_INC_SCI, tx_sc->send_sci) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ES, tx_sc->end_station) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_SCB, tx_sc->scb) ||
	    nla_put_u8(skb, MACSEC_SECY_ATTR_ENCODING_SA, tx_sc->encoding_sa))
		goto cancel;

	if (secy->replay_protect) {
		if (nla_put_u32(skb, MACSEC_SECY_ATTR_WINDOW, secy->replay_window))
			goto cancel;
	}

	nla_nest_end(skb, secy_nest);
	return 0;

cancel:
	nla_nest_cancel(skb, secy_nest);
	return 1;
}