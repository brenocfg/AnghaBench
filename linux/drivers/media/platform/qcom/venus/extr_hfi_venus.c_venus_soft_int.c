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
struct venus_hfi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPU_IC_SOFTINT ; 
 int /*<<< orphan*/  CPU_IC_SOFTINT_H2A_SHIFT ; 
 int /*<<< orphan*/  venus_writel (struct venus_hfi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void venus_soft_int(struct venus_hfi_device *hdev)
{
	venus_writel(hdev, CPU_IC_SOFTINT, BIT(CPU_IC_SOFTINT_H2A_SHIFT));
}