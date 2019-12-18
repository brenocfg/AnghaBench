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
struct pnp_dev {int dummy; } ;
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvt_enable_wake (struct nvt_dev*) ; 
 struct nvt_dev* pnp_get_drvdata (struct pnp_dev*) ; 

__attribute__((used)) static void nvt_shutdown(struct pnp_dev *pdev)
{
	struct nvt_dev *nvt = pnp_get_drvdata(pdev);

	nvt_enable_wake(nvt);
}