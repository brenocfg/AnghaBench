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
struct channel {struct channel* next; struct channel* irb; struct channel* ccw; struct channel* discontact_th; int /*<<< orphan*/  ch_disc_tasklet; int /*<<< orphan*/  ch_tasklet; int /*<<< orphan*/ * trans_skb; int /*<<< orphan*/  fsm; int /*<<< orphan*/  sweep_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTCM_ID_SIZE ; 
 int /*<<< orphan*/  CTC_DBF_INFO ; 
 scalar_t__ IS_MPC (struct channel*) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  channel_free (struct channel*) ; 
 struct channel* channels ; 
 int /*<<< orphan*/  clear_normalized_cda (struct channel*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct channel*) ; 
 int /*<<< orphan*/  kfree_fsm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void channel_remove(struct channel *ch)
{
	struct channel **c = &channels;
	char chid[CTCM_ID_SIZE+1];
	int ok = 0;

	if (ch == NULL)
		return;
	else
		strncpy(chid, ch->id, CTCM_ID_SIZE);

	channel_free(ch);
	while (*c) {
		if (*c == ch) {
			*c = ch->next;
			fsm_deltimer(&ch->timer);
			if (IS_MPC(ch))
				fsm_deltimer(&ch->sweep_timer);

			kfree_fsm(ch->fsm);
			clear_normalized_cda(&ch->ccw[4]);
			if (ch->trans_skb != NULL) {
				clear_normalized_cda(&ch->ccw[1]);
				dev_kfree_skb_any(ch->trans_skb);
			}
			if (IS_MPC(ch)) {
				tasklet_kill(&ch->ch_tasklet);
				tasklet_kill(&ch->ch_disc_tasklet);
				kfree(ch->discontact_th);
			}
			kfree(ch->ccw);
			kfree(ch->irb);
			kfree(ch);
			ok = 1;
			break;
		}
		c = &((*c)->next);
	}

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_INFO, "%s(%s) %s", CTCM_FUNTAIL,
			chid, ok ? "OK" : "failed");
}