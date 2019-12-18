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
typedef  int u32 ;
struct qed_ptt {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int qed_dmae_host2grc (struct qed_hwfn*,struct qed_ptt*,uintptr_t,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_wr (struct qed_hwfn*,struct qed_ptt*,int,int const) ; 

__attribute__((used)) static int qed_init_array_dmae(struct qed_hwfn *p_hwfn,
			       struct qed_ptt *p_ptt,
			       u32 addr,
			       u32 dmae_data_offset,
			       u32 size,
			       const u32 *buf,
			       bool b_must_dmae,
			       bool b_can_dmae)
{
	int rc = 0;

	/* Perform DMAE only for lengthy enough sections or for wide-bus */
	if (!b_can_dmae || (!b_must_dmae && (size < 16))) {
		const u32 *data = buf + dmae_data_offset;
		u32 i;

		for (i = 0; i < size; i++)
			qed_wr(p_hwfn, p_ptt, addr + (i << 2), data[i]);
	} else {
		rc = qed_dmae_host2grc(p_hwfn, p_ptt,
				       (uintptr_t)(buf + dmae_data_offset),
				       addr, size, NULL);
	}

	return rc;
}