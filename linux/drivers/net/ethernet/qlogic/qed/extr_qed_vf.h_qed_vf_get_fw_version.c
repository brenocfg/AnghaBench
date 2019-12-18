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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void qed_vf_get_fw_version(struct qed_hwfn *p_hwfn,
					 u16 *fw_major, u16 *fw_minor,
					 u16 *fw_rev, u16 *fw_eng)
{
}