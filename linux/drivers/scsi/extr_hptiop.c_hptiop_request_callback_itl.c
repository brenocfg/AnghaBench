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
typedef  int u32 ;
struct hptiop_hba {int dummy; } ;

/* Variables and functions */
 int IOPMU_QUEUE_ADDR_HOST_BIT ; 
 int /*<<< orphan*/  hptiop_host_request_callback_itl (struct hptiop_hba*,int) ; 
 int /*<<< orphan*/  hptiop_iop_request_callback_itl (struct hptiop_hba*,int) ; 

__attribute__((used)) static void hptiop_request_callback_itl(struct hptiop_hba *hba, u32 tag)
{
	if (tag & IOPMU_QUEUE_ADDR_HOST_BIT)
		hptiop_host_request_callback_itl(hba,
				tag & ~IOPMU_QUEUE_ADDR_HOST_BIT);
	else
		hptiop_iop_request_callback_itl(hba, tag);
}