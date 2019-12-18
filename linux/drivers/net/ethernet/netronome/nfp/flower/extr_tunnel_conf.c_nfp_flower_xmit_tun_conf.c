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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct nfp_app {int /*<<< orphan*/  ctrl; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_ctrl_tx (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct sk_buff* nfp_flower_cmsg_alloc (struct nfp_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char* nfp_flower_cmsg_get_data (struct sk_buff*) ; 
 int /*<<< orphan*/  nfp_flower_cmsg_get_data_len (struct sk_buff*) ; 

__attribute__((used)) static int
nfp_flower_xmit_tun_conf(struct nfp_app *app, u8 mtype, u16 plen, void *pdata,
			 gfp_t flag)
{
	struct sk_buff *skb;
	unsigned char *msg;

	skb = nfp_flower_cmsg_alloc(app, plen, mtype, flag);
	if (!skb)
		return -ENOMEM;

	msg = nfp_flower_cmsg_get_data(skb);
	memcpy(msg, pdata, nfp_flower_cmsg_get_data_len(skb));

	nfp_ctrl_tx(app->ctrl, skb);
	return 0;
}