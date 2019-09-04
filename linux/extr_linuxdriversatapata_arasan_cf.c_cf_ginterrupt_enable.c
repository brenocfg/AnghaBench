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
struct arasan_cf_dev {scalar_t__ vbase; } ;

/* Variables and functions */
 scalar_t__ GIRQ_SGN_EN ; 
 scalar_t__ GIRQ_STS_EN ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void cf_ginterrupt_enable(struct arasan_cf_dev *acdev, bool enable)
{
	/* enable should be 0 or 1 */
	writel(enable, acdev->vbase + GIRQ_STS_EN);
	writel(enable, acdev->vbase + GIRQ_SGN_EN);
}