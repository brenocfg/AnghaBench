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
struct hnae3_queue {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HNS3_RING_EN_B ; 
 int /*<<< orphan*/  HNS3_RING_EN_REG ; 
 int /*<<< orphan*/  hns3_read_dev (struct hnae3_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns3_write_dev (struct hnae3_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns3_tqp_enable(struct hnae3_queue *tqp)
{
	u32 rcb_reg;

	rcb_reg = hns3_read_dev(tqp, HNS3_RING_EN_REG);
	rcb_reg |= BIT(HNS3_RING_EN_B);
	hns3_write_dev(tqp, HNS3_RING_EN_REG, rcb_reg);
}