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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;
struct TYPE_2__ {int (* send ) (short,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (short,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int xpNotLoaded ; 
 TYPE_1__ xpc_interface ; 

__attribute__((used)) static inline enum xp_retval
xpc_send(short partid, int ch_number, u32 flags, void *payload,
	 u16 payload_size)
{
	if (!xpc_interface.send)
		return xpNotLoaded;

	return xpc_interface.send(partid, ch_number, flags, payload,
				  payload_size);
}