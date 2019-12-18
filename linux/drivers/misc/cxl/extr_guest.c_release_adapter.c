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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cxl_adapter (struct device*) ; 

__attribute__((used)) static void release_adapter(struct device *dev)
{
	free_adapter(to_cxl_adapter(dev));
}