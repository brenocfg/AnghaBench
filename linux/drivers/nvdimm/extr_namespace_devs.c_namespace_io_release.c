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
struct nd_namespace_io {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nd_namespace_io*) ; 
 struct nd_namespace_io* to_nd_namespace_io (struct device*) ; 

__attribute__((used)) static void namespace_io_release(struct device *dev)
{
	struct nd_namespace_io *nsio = to_nd_namespace_io(dev);

	kfree(nsio);
}