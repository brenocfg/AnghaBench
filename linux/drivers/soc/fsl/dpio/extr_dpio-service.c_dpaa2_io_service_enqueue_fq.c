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
typedef  int /*<<< orphan*/  u32 ;
struct qbman_eq_desc {int dummy; } ;
struct dpaa2_io {int /*<<< orphan*/  swp; } ;
struct dpaa2_fd {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  qbman_eq_desc_clear (struct qbman_eq_desc*) ; 
 int /*<<< orphan*/  qbman_eq_desc_set_fq (struct qbman_eq_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_eq_desc_set_no_orp (struct qbman_eq_desc*,int /*<<< orphan*/ ) ; 
 int qbman_swp_enqueue (int /*<<< orphan*/ ,struct qbman_eq_desc*,struct dpaa2_fd const*) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 

int dpaa2_io_service_enqueue_fq(struct dpaa2_io *d,
				u32 fqid,
				const struct dpaa2_fd *fd)
{
	struct qbman_eq_desc ed;

	d = service_select(d);
	if (!d)
		return -ENODEV;

	qbman_eq_desc_clear(&ed);
	qbman_eq_desc_set_no_orp(&ed, 0);
	qbman_eq_desc_set_fq(&ed, fqid);

	return qbman_swp_enqueue(d->swp, &ed, fd);
}