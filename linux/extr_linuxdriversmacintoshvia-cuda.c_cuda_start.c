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
struct TYPE_2__ {int* data; } ;

/* Variables and functions */
 size_t ACR ; 
 size_t B ; 
 size_t SR ; 
 int SR_OUT ; 
 scalar_t__ TREQ_asserted (int) ; 
 int /*<<< orphan*/  assert_TIP () ; 
 int /*<<< orphan*/  assert_TIP_and_TACK () ; 
 int /*<<< orphan*/  cuda_state ; 
 TYPE_1__* current_req ; 
 scalar_t__ data_index ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 scalar_t__ mcu_is_egret ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sent_first_byte ; 
 int /*<<< orphan*/ * via ; 

__attribute__((used)) static void
cuda_start(void)
{
    /* assert cuda_state == idle */
    if (current_req == NULL)
	return;
    data_index = 0;
    if (TREQ_asserted(in_8(&via[B])))
	return;			/* a byte is coming in from the CUDA */

    /* set the shift register to shift out and send a byte */
    out_8(&via[ACR], in_8(&via[ACR]) | SR_OUT);
    out_8(&via[SR], current_req->data[data_index++]);
    if (mcu_is_egret)
	assert_TIP_and_TACK();
    else
	assert_TIP();
    cuda_state = sent_first_byte;
}