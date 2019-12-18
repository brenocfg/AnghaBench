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
struct dpaa2_dq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qbman_result_is_DQ (struct dpaa2_dq const*) ; 

__attribute__((used)) static inline int qbman_result_is_SCN(const struct dpaa2_dq *dq)
{
	return !qbman_result_is_DQ(dq);
}