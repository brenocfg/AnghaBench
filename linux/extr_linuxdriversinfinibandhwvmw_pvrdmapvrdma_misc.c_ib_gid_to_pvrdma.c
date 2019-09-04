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
typedef  union pvrdma_gid {int dummy; } pvrdma_gid ;
typedef  union ib_gid {int dummy; } ib_gid ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  memcpy (union pvrdma_gid*,union ib_gid const*,int) ; 

void ib_gid_to_pvrdma(union pvrdma_gid *dst, const union ib_gid *src)
{
	BUILD_BUG_ON(sizeof(union pvrdma_gid) != sizeof(union ib_gid));
	memcpy(dst, src, sizeof(*src));
}