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
typedef  enum pvrdma_wc_status { ____Placeholder_pvrdma_wc_status } pvrdma_wc_status ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */

__attribute__((used)) static inline enum ib_wc_status pvrdma_wc_status_to_ib(
					enum pvrdma_wc_status status)
{
	return (enum ib_wc_status)status;
}