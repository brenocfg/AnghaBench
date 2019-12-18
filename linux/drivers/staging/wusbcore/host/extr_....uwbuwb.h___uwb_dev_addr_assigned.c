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
struct uwb_rc {int dummy; } ;
struct uwb_dev_addr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __uwb_dev_addr_assigned_check ; 
 int uwb_dev_for_each (struct uwb_rc*,int /*<<< orphan*/ ,struct uwb_dev_addr*) ; 

__attribute__((used)) static inline unsigned __uwb_dev_addr_assigned(struct uwb_rc *rc,
					       struct uwb_dev_addr *addr)
{
	return uwb_dev_for_each(rc, __uwb_dev_addr_assigned_check, addr);
}