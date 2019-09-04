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
struct qed_ooo_info {int dummy; } ;
struct qed_ooo_buffer {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct qed_ooo_buffer *
qed_ooo_get_free_buffer(struct qed_hwfn *p_hwfn,
			struct qed_ooo_info *p_ooo_info) { return NULL; }