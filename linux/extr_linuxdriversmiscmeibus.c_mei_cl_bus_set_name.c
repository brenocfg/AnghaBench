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
struct mei_cl_device {int /*<<< orphan*/  me_cl; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_ver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mei_cl_bus_set_name(struct mei_cl_device *cldev)
{
	dev_set_name(&cldev->dev, "mei:%s:%pUl:%02X",
		     cldev->name,
		     mei_me_cl_uuid(cldev->me_cl),
		     mei_me_cl_ver(cldev->me_cl));
}