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
typedef  int /*<<< orphan*/  u8 ;
struct recv_frame {TYPE_1__* pkt; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct adapter {int dummy; } ;
struct action_handler {unsigned char num; int /*<<< orphan*/  (* func ) (struct adapter*,struct recv_frame*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct action_handler*) ; 
 struct action_handler* OnAction_tbl ; 
 unsigned int _SUCCESS ; 
 int /*<<< orphan*/  stub1 (struct adapter*,struct recv_frame*) ; 

__attribute__((used)) static unsigned int OnAction(struct adapter *padapter,
			     struct recv_frame *precv_frame)
{
	int i;
	unsigned char category;
	struct action_handler *ptable;
	unsigned char *frame_body;
	u8 *pframe = precv_frame->pkt->data;

	frame_body = (unsigned char *)(pframe + sizeof(struct ieee80211_hdr_3addr));

	category = frame_body[0];

	for (i = 0; i < ARRAY_SIZE(OnAction_tbl); i++) {
		ptable = &OnAction_tbl[i];
		if (category == ptable->num)
			ptable->func(padapter, precv_frame);
	}
	return _SUCCESS;
}