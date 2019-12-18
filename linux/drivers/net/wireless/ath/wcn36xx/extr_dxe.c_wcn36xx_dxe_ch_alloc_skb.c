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
struct wcn36xx_dxe_ctl {struct wcn36xx_dxe_ctl* next; } ;
struct wcn36xx_dxe_ch {int desc_num; struct wcn36xx_dxe_ctl* head_blk_ctl; } ;
struct wcn36xx {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  wcn36xx_dxe_fill_skb (int /*<<< orphan*/ ,struct wcn36xx_dxe_ctl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wcn36xx_dxe_ch_alloc_skb(struct wcn36xx *wcn,
				    struct wcn36xx_dxe_ch *wcn_ch)
{
	int i;
	struct wcn36xx_dxe_ctl *cur_ctl = NULL;

	cur_ctl = wcn_ch->head_blk_ctl;

	for (i = 0; i < wcn_ch->desc_num; i++) {
		wcn36xx_dxe_fill_skb(wcn->dev, cur_ctl, GFP_KERNEL);
		cur_ctl = cur_ctl->next;
	}

	return 0;
}