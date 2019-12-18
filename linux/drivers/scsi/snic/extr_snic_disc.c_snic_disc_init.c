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
struct snic_disc {int /*<<< orphan*/ * cb; int /*<<< orphan*/ * rtgt_info; scalar_t__ rtgt_cnt; scalar_t__ req_cnt; int /*<<< orphan*/  state; scalar_t__ nxt_tgt_id; scalar_t__ disc_id; int /*<<< orphan*/  mutex; int /*<<< orphan*/  tgt_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SNIC_DISC_INIT ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void
snic_disc_init(struct snic_disc *disc)
{
	INIT_LIST_HEAD(&disc->tgt_list);
	mutex_init(&disc->mutex);
	disc->disc_id = 0;
	disc->nxt_tgt_id = 0;
	disc->state = SNIC_DISC_INIT;
	disc->req_cnt = 0;
	disc->rtgt_cnt = 0;
	disc->rtgt_info = NULL;
	disc->cb = NULL;
}