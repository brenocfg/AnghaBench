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
struct intel_ntb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndev_deinit_isr (struct intel_ntb_dev*) ; 

__attribute__((used)) static void xeon_deinit_isr(struct intel_ntb_dev *ndev)
{
	ndev_deinit_isr(ndev);
}