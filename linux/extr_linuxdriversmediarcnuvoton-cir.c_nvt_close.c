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
struct rc_dev {struct nvt_dev* priv; } ;
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nvt_disable_cir (struct nvt_dev*) ; 

__attribute__((used)) static void nvt_close(struct rc_dev *dev)
{
	struct nvt_dev *nvt = dev->priv;

	nvt_disable_cir(nvt);
}