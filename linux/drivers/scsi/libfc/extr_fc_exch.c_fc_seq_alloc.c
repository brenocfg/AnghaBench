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
struct fc_seq {int /*<<< orphan*/  id; scalar_t__ cnt; scalar_t__ ssb_stat; } ;
struct fc_exch {struct fc_seq seq; } ;

/* Variables and functions */

__attribute__((used)) static struct fc_seq *fc_seq_alloc(struct fc_exch *ep, u8 seq_id)
{
	struct fc_seq *sp;

	sp = &ep->seq;
	sp->ssb_stat = 0;
	sp->cnt = 0;
	sp->id = seq_id;
	return sp;
}