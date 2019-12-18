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
struct hnae_handle {int q_num; int /*<<< orphan*/ * qs; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns_rcb_ring_enable_hw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_ae_ring_enable_all(struct hnae_handle *handle, int val)
{
	int q_num = handle->q_num;
	int i;

	for (i = 0; i < q_num; i++)
		hns_rcb_ring_enable_hw(handle->qs[i], val);
}