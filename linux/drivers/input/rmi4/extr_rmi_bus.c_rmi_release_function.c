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
struct rmi_function {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rmi_function*) ; 
 struct rmi_function* to_rmi_function (struct device*) ; 

__attribute__((used)) static void rmi_release_function(struct device *dev)
{
	struct rmi_function *fn = to_rmi_function(dev);

	kfree(fn);
}