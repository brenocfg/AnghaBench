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
struct smt_entry {scalar_t__ refcnt; scalar_t__ state; int /*<<< orphan*/  src_mac; } ;
struct smt_data {size_t smt_size; struct smt_entry* smtab; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ SMT_STATE_SWITCHING ; 
 scalar_t__ SMT_STATE_UNUSED ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct smt_entry *find_or_alloc_smte(struct smt_data *s, u8 *smac)
{
	struct smt_entry *first_free = NULL;
	struct smt_entry *e, *end;

	for (e = &s->smtab[0], end = &s->smtab[s->smt_size]; e != end; ++e) {
		if (e->refcnt == 0) {
			if (!first_free)
				first_free = e;
		} else {
			if (e->state == SMT_STATE_SWITCHING) {
				/* This entry is actually in use. See if we can
				 * re-use it ?
				 */
				if (memcmp(e->src_mac, smac, ETH_ALEN) == 0)
					goto found_reuse;
			}
		}
	}

	if (first_free) {
		e = first_free;
		goto found;
	}
	return NULL;

found:
	e->state = SMT_STATE_UNUSED;

found_reuse:
	return e;
}