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
struct amba_id {int dummy; } ;
struct amba_device {int /*<<< orphan*/  res; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int replicator_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dynamic_replicator_probe(struct amba_device *adev,
				    const struct amba_id *id)
{
	return replicator_probe(&adev->dev, &adev->res);
}