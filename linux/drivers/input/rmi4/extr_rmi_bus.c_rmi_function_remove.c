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
struct rmi_function_handler {int /*<<< orphan*/  (* remove ) (struct rmi_function*) ;} ;
struct rmi_function {int dummy; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rmi_function*) ; 
 struct rmi_function* to_rmi_function (struct device*) ; 
 struct rmi_function_handler* to_rmi_function_handler (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rmi_function_remove(struct device *dev)
{
	struct rmi_function *fn = to_rmi_function(dev);
	struct rmi_function_handler *handler =
					to_rmi_function_handler(dev->driver);

	if (handler->remove)
		handler->remove(fn);

	return 0;
}