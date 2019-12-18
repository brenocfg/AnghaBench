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
struct cedrus_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VE_MODE ; 
 int /*<<< orphan*/  VE_MODE_DISABLED ; 
 int /*<<< orphan*/  cedrus_write (struct cedrus_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cedrus_engine_disable(struct cedrus_dev *dev)
{
	cedrus_write(dev, VE_MODE, VE_MODE_DISABLED);
}