#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_4__ {TYPE_2__* hyctrlinfo; } ;
typedef  TYPE_1__ hysdn_card ;
struct TYPE_5__ {size_t out_idx; struct sk_buff** skbs; int /*<<< orphan*/  sk_count; } ;
typedef  TYPE_2__ hycapictrl_info ;

/* Variables and functions */

struct sk_buff *
hycapi_tx_capiget(hysdn_card *card)
{
	hycapictrl_info *cinfo = card->hyctrlinfo;
	if (!cinfo) {
		return (struct sk_buff *)NULL;
	}
	if (!cinfo->sk_count)
		return (struct sk_buff *)NULL;	/* nothing available */

	return (cinfo->skbs[cinfo->out_idx]);		/* next packet to send */
}