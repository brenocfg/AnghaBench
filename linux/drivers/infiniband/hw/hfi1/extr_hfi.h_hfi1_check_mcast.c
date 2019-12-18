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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  OPA_LID_PERMISSIVE ; 
 int /*<<< orphan*/  OPA_MCAST_NR ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ opa_get_mcast_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool hfi1_check_mcast(u32 lid)
{
	return ((lid >= opa_get_mcast_base(OPA_MCAST_NR)) &&
		(lid != be32_to_cpu(OPA_LID_PERMISSIVE)));
}