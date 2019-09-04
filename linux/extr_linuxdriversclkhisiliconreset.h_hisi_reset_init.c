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
struct platform_device {int dummy; } ;
struct hisi_reset_controller {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct hisi_reset_controller *hisi_reset_init(struct platform_device *pdev)
{
	return 0;
}