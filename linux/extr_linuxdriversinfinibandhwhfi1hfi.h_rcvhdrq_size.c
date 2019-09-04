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
struct hfi1_ctxtdata {int rcvhdrq_cnt; int rcvhdrqentsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (int) ; 

__attribute__((used)) static inline u32 rcvhdrq_size(struct hfi1_ctxtdata *rcd)
{
	return PAGE_ALIGN(rcd->rcvhdrq_cnt *
			  rcd->rcvhdrqentsize * sizeof(u32));
}