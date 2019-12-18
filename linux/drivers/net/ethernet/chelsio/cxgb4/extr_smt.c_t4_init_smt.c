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
struct smt_data {unsigned int smt_size; TYPE_1__* smtab; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int idx; scalar_t__ refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int SMT_SIZE ; 
 int /*<<< orphan*/  SMT_STATE_UNUSED ; 
 struct smt_data* kvzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smtab ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  struct_size (struct smt_data*,int /*<<< orphan*/ ,unsigned int) ; 

struct smt_data *t4_init_smt(void)
{
	unsigned int smt_size;
	struct smt_data *s;
	int i;

	smt_size = SMT_SIZE;

	s = kvzalloc(struct_size(s, smtab, smt_size), GFP_KERNEL);
	if (!s)
		return NULL;
	s->smt_size = smt_size;
	rwlock_init(&s->lock);
	for (i = 0; i < s->smt_size; ++i) {
		s->smtab[i].idx = i;
		s->smtab[i].state = SMT_STATE_UNUSED;
		memset(&s->smtab[i].src_mac, 0, ETH_ALEN);
		spin_lock_init(&s->smtab[i].lock);
		s->smtab[i].refcnt = 0;
	}
	return s;
}