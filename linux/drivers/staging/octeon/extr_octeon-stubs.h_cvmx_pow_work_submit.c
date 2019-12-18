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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum cvmx_pow_tag_type { ____Placeholder_cvmx_pow_tag_type } cvmx_pow_tag_type ;
typedef  int /*<<< orphan*/  cvmx_wqe_t ;

/* Variables and functions */

__attribute__((used)) static inline void cvmx_pow_work_submit(cvmx_wqe_t *wqp, uint32_t tag,
					enum cvmx_pow_tag_type tag_type,
					uint64_t qos, uint64_t grp)
{ }