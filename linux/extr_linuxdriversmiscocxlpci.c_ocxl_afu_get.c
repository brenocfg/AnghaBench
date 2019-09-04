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
struct ocxl_afu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/ * get_device (int /*<<< orphan*/ *) ; 

struct ocxl_afu *ocxl_afu_get(struct ocxl_afu *afu)
{
	return (get_device(&afu->dev) == NULL) ? NULL : afu;
}