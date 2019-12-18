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
struct ib_sa_query {int flags; } ;

/* Variables and functions */
 int IB_SA_CANCEL ; 

__attribute__((used)) static inline int ib_sa_query_cancelled(struct ib_sa_query *query)
{
	return (query->flags & IB_SA_CANCEL);
}