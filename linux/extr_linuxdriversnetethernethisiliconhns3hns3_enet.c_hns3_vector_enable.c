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
struct hns3_enet_tqp_vector {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_mask_vector_irq (struct hns3_enet_tqp_vector*,int) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hns3_vector_enable(struct hns3_enet_tqp_vector *tqp_vector)
{
	napi_enable(&tqp_vector->napi);

	/* enable vector */
	hns3_mask_vector_irq(tqp_vector, 1);
}