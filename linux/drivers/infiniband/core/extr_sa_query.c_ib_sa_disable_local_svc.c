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
struct ib_sa_query {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SA_ENABLE_LOCAL_SERVICE ; 

__attribute__((used)) static inline void ib_sa_disable_local_svc(struct ib_sa_query *query)
{
	query->flags &= ~IB_SA_ENABLE_LOCAL_SERVICE;
}