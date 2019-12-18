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
struct pppox_proto {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int EINVAL ; 
 int PX_MAX_PROTO ; 
 struct pppox_proto const** pppox_protos ; 

int register_pppox_proto(int proto_num, const struct pppox_proto *pp)
{
	if (proto_num < 0 || proto_num > PX_MAX_PROTO)
		return -EINVAL;
	if (pppox_protos[proto_num])
		return -EALREADY;
	pppox_protos[proto_num] = pp;
	return 0;
}