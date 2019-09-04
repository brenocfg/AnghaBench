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
struct qlcnic_dcb {int /*<<< orphan*/  aen_work; int /*<<< orphan*/  wq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int BIT_8 ; 
 int /*<<< orphan*/  QLCNIC_DCB_AEN_MODE ; 
 int /*<<< orphan*/  QLCNIC_DCB_STATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qlcnic_83xx_dcb_aen_handler(struct qlcnic_dcb *dcb, void *data)
{
	u32 *val = data;

	if (test_and_set_bit(QLCNIC_DCB_AEN_MODE, &dcb->state))
		return;

	if (*val & BIT_8)
		set_bit(QLCNIC_DCB_STATE, &dcb->state);
	else
		clear_bit(QLCNIC_DCB_STATE, &dcb->state);

	queue_delayed_work(dcb->wq, &dcb->aen_work, 0);
}