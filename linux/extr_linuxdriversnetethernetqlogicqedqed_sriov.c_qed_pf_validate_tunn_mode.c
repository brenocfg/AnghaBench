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
struct qed_tunn_update_type {int b_update_mode; int /*<<< orphan*/  b_mode_enabled; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static void qed_pf_validate_tunn_mode(struct qed_tunn_update_type *tun, int *rc)
{
	if (tun->b_update_mode && !tun->b_mode_enabled) {
		tun->b_update_mode = false;
		*rc = -EINVAL;
	}
}