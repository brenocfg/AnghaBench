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
struct wcn36xx_dxe_ctl {int ctl_blk_order; struct wcn36xx_dxe_ctl* next; } ;
struct wcn36xx_dxe_ch {int desc_num; struct wcn36xx_dxe_ctl* head_blk_ctl; struct wcn36xx_dxe_ctl* tail_blk_ctl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct wcn36xx_dxe_ctl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dxe_free_ctl_block (struct wcn36xx_dxe_ch*) ; 

__attribute__((used)) static int wcn36xx_dxe_allocate_ctl_block(struct wcn36xx_dxe_ch *ch)
{
	struct wcn36xx_dxe_ctl *prev_ctl = NULL;
	struct wcn36xx_dxe_ctl *cur_ctl = NULL;
	int i;

	spin_lock_init(&ch->lock);
	for (i = 0; i < ch->desc_num; i++) {
		cur_ctl = kzalloc(sizeof(*cur_ctl), GFP_KERNEL);
		if (!cur_ctl)
			goto out_fail;

		cur_ctl->ctl_blk_order = i;
		if (i == 0) {
			ch->head_blk_ctl = cur_ctl;
			ch->tail_blk_ctl = cur_ctl;
		} else if (ch->desc_num - 1 == i) {
			prev_ctl->next = cur_ctl;
			cur_ctl->next = ch->head_blk_ctl;
		} else {
			prev_ctl->next = cur_ctl;
		}
		prev_ctl = cur_ctl;
	}

	return 0;

out_fail:
	wcn36xx_dxe_free_ctl_block(ch);
	return -ENOMEM;
}