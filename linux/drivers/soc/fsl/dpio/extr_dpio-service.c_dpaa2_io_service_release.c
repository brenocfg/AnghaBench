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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct qbman_release_desc {int dummy; } ;
struct dpaa2_io {int /*<<< orphan*/  swp; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  qbman_release_desc_clear (struct qbman_release_desc*) ; 
 int /*<<< orphan*/  qbman_release_desc_set_bpid (struct qbman_release_desc*,int /*<<< orphan*/ ) ; 
 int qbman_swp_release (int /*<<< orphan*/ ,struct qbman_release_desc*,int /*<<< orphan*/  const*,unsigned int) ; 
 struct dpaa2_io* service_select (struct dpaa2_io*) ; 

int dpaa2_io_service_release(struct dpaa2_io *d,
			     u16 bpid,
			     const u64 *buffers,
			     unsigned int num_buffers)
{
	struct qbman_release_desc rd;

	d = service_select(d);
	if (!d)
		return -ENODEV;

	qbman_release_desc_clear(&rd);
	qbman_release_desc_set_bpid(&rd, bpid);

	return qbman_swp_release(d->swp, &rd, buffers, num_buffers);
}