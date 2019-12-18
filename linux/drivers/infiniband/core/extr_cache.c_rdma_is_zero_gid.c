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
typedef  union ib_gid {int dummy; } ib_gid ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (union ib_gid const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zgid ; 

bool rdma_is_zero_gid(const union ib_gid *gid)
{
	return !memcmp(gid, &zgid, sizeof(*gid));
}