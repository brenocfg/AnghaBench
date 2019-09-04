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
struct pl172_data {int /*<<< orphan*/  clk; } ;
struct amba_device {int dummy; } ;

/* Variables and functions */
 struct pl172_data* amba_get_drvdata (struct amba_device*) ; 
 int /*<<< orphan*/  amba_release_regions (struct amba_device*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl172_remove(struct amba_device *adev)
{
	struct pl172_data *pl172 = amba_get_drvdata(adev);

	clk_disable_unprepare(pl172->clk);
	amba_release_regions(adev);

	return 0;
}