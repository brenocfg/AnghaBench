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
struct wcn36xx_dxe_ctl {struct wcn36xx_dxe_ctl* next; int /*<<< orphan*/  skb; } ;
struct wcn36xx_dxe_ch {int desc_num; struct wcn36xx_dxe_ctl* head_blk_ctl; } ;
struct wcn36xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wcn36xx_dxe_ch_free_skbs(struct wcn36xx *wcn,
				     struct wcn36xx_dxe_ch *wcn_ch)
{
	struct wcn36xx_dxe_ctl *cur = wcn_ch->head_blk_ctl;
	int i;

	for (i = 0; i < wcn_ch->desc_num; i++) {
		kfree_skb(cur->skb);
		cur = cur->next;
	}
}