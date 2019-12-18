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
struct qm_sg_entry {scalar_t__ bpid; } ;
struct dpaa_bp {int dummy; } ;
struct bm_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  bmb ;

/* Variables and functions */
 int ARRAY_SIZE (struct bm_buffer*) ; 
 int DPAA_BUFF_RELEASE_MAX ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_buffer_set64 (struct bm_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa_bman_release (struct dpaa_bp*,struct bm_buffer*,int) ; 
 struct dpaa_bp* dpaa_bpid2pool (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct bm_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qm_sg_entry_get64 (struct qm_sg_entry*) ; 
 int /*<<< orphan*/  qm_sg_entry_is_ext (struct qm_sg_entry*) ; 
 int /*<<< orphan*/  qm_sg_entry_is_final (struct qm_sg_entry*) ; 

__attribute__((used)) static void dpaa_release_sgt_members(struct qm_sg_entry *sgt)
{
	struct bm_buffer bmb[DPAA_BUFF_RELEASE_MAX];
	struct dpaa_bp *dpaa_bp;
	int i = 0, j;

	memset(bmb, 0, sizeof(bmb));

	do {
		dpaa_bp = dpaa_bpid2pool(sgt[i].bpid);
		if (!dpaa_bp)
			return;

		j = 0;
		do {
			WARN_ON(qm_sg_entry_is_ext(&sgt[i]));

			bm_buffer_set64(&bmb[j], qm_sg_entry_get64(&sgt[i]));

			j++; i++;
		} while (j < ARRAY_SIZE(bmb) &&
				!qm_sg_entry_is_final(&sgt[i - 1]) &&
				sgt[i - 1].bpid == sgt[i].bpid);

		dpaa_bman_release(dpaa_bp, bmb, j);
	} while (!qm_sg_entry_is_final(&sgt[i - 1]));
}