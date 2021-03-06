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
typedef  int /*<<< orphan*/  u32 ;
struct nd_namespace_index {int dummy; } ;

/* Variables and functions */
 size_t ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NSINDEX_ALIGN ; 

__attribute__((used)) static size_t __sizeof_namespace_index(u32 nslot)
{
	return ALIGN(sizeof(struct nd_namespace_index) + DIV_ROUND_UP(nslot, 8),
			NSINDEX_ALIGN);
}