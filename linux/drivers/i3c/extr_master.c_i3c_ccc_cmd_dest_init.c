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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {void* data; scalar_t__ len; } ;
struct i3c_ccc_cmd_dest {TYPE_1__ payload; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *i3c_ccc_cmd_dest_init(struct i3c_ccc_cmd_dest *dest, u8 addr,
				   u16 payloadlen)
{
	dest->addr = addr;
	dest->payload.len = payloadlen;
	if (payloadlen)
		dest->payload.data = kzalloc(payloadlen, GFP_KERNEL);
	else
		dest->payload.data = NULL;

	return dest->payload.data;
}