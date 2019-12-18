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
struct ql_adapter {unsigned int lbq_buf_order; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 

__attribute__((used)) static inline unsigned int ql_lbq_block_size(struct ql_adapter *qdev)
{
	return PAGE_SIZE << qdev->lbq_buf_order;
}