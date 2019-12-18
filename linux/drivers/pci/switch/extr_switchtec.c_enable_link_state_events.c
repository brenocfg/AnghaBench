#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct switchtec_dev {int pff_csr_count; TYPE_1__* mmio_pff_csr; } ;
struct TYPE_2__ {int /*<<< orphan*/  link_state_hdr; } ;

/* Variables and functions */
 int SWITCHTEC_EVENT_CLEAR ; 
 int SWITCHTEC_EVENT_EN_IRQ ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enable_link_state_events(struct switchtec_dev *stdev)
{
	int idx;

	for (idx = 0; idx < stdev->pff_csr_count; idx++) {
		iowrite32(SWITCHTEC_EVENT_CLEAR |
			  SWITCHTEC_EVENT_EN_IRQ,
			  &stdev->mmio_pff_csr[idx].link_state_hdr);
	}
}