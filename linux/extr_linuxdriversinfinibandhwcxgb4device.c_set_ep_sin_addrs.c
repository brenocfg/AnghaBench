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
struct sockaddr_in {int dummy; } ;
struct iw_cm_id {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/  local_addr; struct iw_cm_id* cm_id; } ;
struct c4iw_ep {TYPE_1__ com; } ;

/* Variables and functions */
 struct sockaddr_in zero_sin ; 

__attribute__((used)) static void set_ep_sin_addrs(struct c4iw_ep *ep,
			     struct sockaddr_in **lsin,
			     struct sockaddr_in **rsin,
			     struct sockaddr_in **m_lsin,
			     struct sockaddr_in **m_rsin)
{
	struct iw_cm_id *id = ep->com.cm_id;

	*m_lsin = (struct sockaddr_in *)&ep->com.local_addr;
	*m_rsin = (struct sockaddr_in *)&ep->com.remote_addr;
	if (id) {
		*lsin = (struct sockaddr_in *)&id->local_addr;
		*rsin = (struct sockaddr_in *)&id->remote_addr;
	} else {
		*lsin = &zero_sin;
		*rsin = &zero_sin;
	}
}