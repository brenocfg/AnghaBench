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
struct nfp_resource {int /*<<< orphan*/  cpp_id; } ;

/* Variables and functions */

u32 nfp_resource_cpp_id(struct nfp_resource *res)
{
	return res->cpp_id;
}