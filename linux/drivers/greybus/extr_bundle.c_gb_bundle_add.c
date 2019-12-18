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
struct gb_bundle {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_bundle_add (struct gb_bundle*) ; 

int gb_bundle_add(struct gb_bundle *bundle)
{
	int ret;

	ret = device_add(&bundle->dev);
	if (ret) {
		dev_err(&bundle->dev, "failed to register bundle: %d\n", ret);
		return ret;
	}

	trace_gb_bundle_add(bundle);

	return 0;
}