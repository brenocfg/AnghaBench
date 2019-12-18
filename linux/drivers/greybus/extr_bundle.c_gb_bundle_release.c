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
struct gb_bundle {struct gb_bundle* cport_desc; struct gb_bundle* state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gb_bundle*) ; 
 struct gb_bundle* to_gb_bundle (struct device*) ; 
 int /*<<< orphan*/  trace_gb_bundle_release (struct gb_bundle*) ; 

__attribute__((used)) static void gb_bundle_release(struct device *dev)
{
	struct gb_bundle *bundle = to_gb_bundle(dev);

	trace_gb_bundle_release(bundle);

	kfree(bundle->state);
	kfree(bundle->cport_desc);
	kfree(bundle);
}