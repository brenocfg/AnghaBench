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
struct hns3_enet_tqp_vector {scalar_t__ mask_addr; } ;

/* Variables and functions */
 scalar_t__ HNS3_VECTOR_GL0_OFFSET ; 
 int /*<<< orphan*/  hns3_gl_usec_to_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void hns3_set_vector_coalesce_rx_gl(struct hns3_enet_tqp_vector *tqp_vector,
				    u32 gl_value)
{
	u32 rx_gl_reg = hns3_gl_usec_to_reg(gl_value);

	writel(rx_gl_reg, tqp_vector->mask_addr + HNS3_VECTOR_GL0_OFFSET);
}