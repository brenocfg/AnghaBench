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
typedef  int /*<<< orphan*/  u64 ;
struct ib_header {int dummy; } ;

/* Variables and functions */
 int ib_get_sc (struct ib_header*) ; 
 int /*<<< orphan*/  rhf_dc_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int hfi1_9B_get_sc5(struct ib_header *hdr, u64 rhf)
{
	return ib_get_sc(hdr) | ((!!(rhf_dc_info(rhf))) << 4);
}