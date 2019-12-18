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
struct t10_pi_tuple {int dummy; } ;
struct nvme_ns {int ms; scalar_t__ pi_type; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nvme_ns_has_pi(struct nvme_ns *ns)
{
	return ns->pi_type && ns->ms == sizeof(struct t10_pi_tuple);
}