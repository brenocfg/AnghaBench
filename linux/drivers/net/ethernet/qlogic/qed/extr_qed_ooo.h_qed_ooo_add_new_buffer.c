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
struct qed_ooo_info {int dummy; } ;
struct qed_ooo_buffer {int dummy; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void qed_ooo_add_new_buffer(struct qed_hwfn *p_hwfn,
					  struct qed_ooo_info *p_ooo_info,
					  u32 cid, u8 ooo_isle,
					  struct qed_ooo_buffer *p_buffer,
					  u8 buffer_side) {}