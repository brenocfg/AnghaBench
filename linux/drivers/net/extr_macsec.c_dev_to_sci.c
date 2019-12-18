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
struct net_device {int /*<<< orphan*/  dev_addr; } ;
typedef  int /*<<< orphan*/  sci_t ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  make_sci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static sci_t dev_to_sci(struct net_device *dev, __be16 port)
{
	return make_sci(dev->dev_addr, port);
}