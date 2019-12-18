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
struct rio_mport {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT ; 
 struct rio_mport* to_rio_mport (struct device*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_mport_release(struct device *dev)
{
	struct rio_mport *mport = to_rio_mport(dev);

	tsi_debug(EXIT, dev, "%s id=%d", mport->name, mport->id);
}