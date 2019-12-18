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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum ib_gid_type { ____Placeholder_ib_gid_type } ib_gid_type ;

/* Variables and functions */
 int IB_GID_TYPE_ROCE_UDP_ENCAP ; 
 int /*<<< orphan*/  PVRDMA_GID_TYPE_FLAG_ROCE_V1 ; 
 int /*<<< orphan*/  PVRDMA_GID_TYPE_FLAG_ROCE_V2 ; 

u8 ib_gid_type_to_pvrdma(enum ib_gid_type gid_type)
{
	return (gid_type == IB_GID_TYPE_ROCE_UDP_ENCAP) ?
		PVRDMA_GID_TYPE_FLAG_ROCE_V2 :
		PVRDMA_GID_TYPE_FLAG_ROCE_V1;
}