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
struct nfp_dumpspec_cpp_isl_id {int /*<<< orphan*/  island; int /*<<< orphan*/  token; int /*<<< orphan*/  action; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_CPP_ISLAND_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 nfp_get_numeric_cpp_id(struct nfp_dumpspec_cpp_isl_id *cpp_id)
{
	return NFP_CPP_ISLAND_ID(cpp_id->target, cpp_id->action, cpp_id->token,
				 cpp_id->island);
}