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
struct TYPE_2__ {scalar_t__ nports; } ;
struct adapter {TYPE_1__ params; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static inline void *interfaces_get_idx(struct adapter *adapter, loff_t pos)
{
	return pos <= adapter->params.nports
		? (void *)(uintptr_t)(pos + 1)
		: NULL;
}