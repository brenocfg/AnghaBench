#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct dpaa2_dq {TYPE_1__ scn; } ;

/* Variables and functions */

__attribute__((used)) static inline u8 qbman_result_SCN_state(const struct dpaa2_dq *scn)
{
	return scn->scn.state;
}