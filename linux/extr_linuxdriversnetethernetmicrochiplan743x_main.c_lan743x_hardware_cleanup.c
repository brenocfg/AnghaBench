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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_EN_CLR ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan743x_hardware_cleanup(struct lan743x_adapter *adapter)
{
	lan743x_csr_write(adapter, INT_EN_CLR, 0xFFFFFFFF);
}