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
struct qcom_glink {TYPE_1__* tx_pipe; } ;
struct TYPE_2__ {size_t (* avail ) (TYPE_1__*) ;} ;

/* Variables and functions */
 size_t stub1 (TYPE_1__*) ; 

__attribute__((used)) static size_t qcom_glink_tx_avail(struct qcom_glink *glink)
{
	return glink->tx_pipe->avail(glink->tx_pipe);
}