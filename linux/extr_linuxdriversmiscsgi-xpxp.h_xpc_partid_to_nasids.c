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
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int (* partid_to_nasids ) (short,void*) ;} ;

/* Variables and functions */
 int stub1 (short,void*) ; 
 int xpNotLoaded ; 
 TYPE_1__ xpc_interface ; 

__attribute__((used)) static inline enum xp_retval
xpc_partid_to_nasids(short partid, void *nasids)
{
	if (!xpc_interface.partid_to_nasids)
		return xpNotLoaded;

	return xpc_interface.partid_to_nasids(partid, nasids);
}