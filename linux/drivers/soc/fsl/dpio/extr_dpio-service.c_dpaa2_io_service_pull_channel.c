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
typedef  int /*<<< orphan*/  u32 ;
struct qbman_pull_desc {int dummy; } ;
struct dpaa2_io_store {int /*<<< orphan*/ * swp; scalar_t__ max; int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; } ;
struct dpaa2_io {int /*<<< orphan*/ * swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  qbman_pull_desc_clear (struct qbman_pull_desc*) ; 
 int /*<<< orphan*/  qbman_pull_desc_set_channel (struct qbman_pull_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_pull_desc_set_numframes (struct qbman_pull_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_pull_desc_set_storage (struct qbman_pull_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qbman_pull_type_prio ; 
 int qbman_swp_pull (int /*<<< orphan*/ *,struct qbman_pull_desc*) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 

int dpaa2_io_service_pull_channel(struct dpaa2_io *d, u32 channelid,
				  struct dpaa2_io_store *s)
{
	struct qbman_pull_desc pd;
	int err;

	qbman_pull_desc_clear(&pd);
	qbman_pull_desc_set_storage(&pd, s->vaddr, s->paddr, 1);
	qbman_pull_desc_set_numframes(&pd, (u8)s->max);
	qbman_pull_desc_set_channel(&pd, channelid, qbman_pull_type_prio);

	d = service_select(d);
	if (!d)
		return -ENODEV;

	s->swp = d->swp;
	err = qbman_swp_pull(d->swp, &pd);
	if (err)
		s->swp = NULL;

	return err;
}