#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* device; } ;
struct nvkm_bios {TYPE_2__ subdev; } ;
struct firmware {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int request_firmware (struct firmware const**,char const*,struct device*) ; 

__attribute__((used)) static void *
shadow_fw_init(struct nvkm_bios *bios, const char *name)
{
	struct device *dev = bios->subdev.device->dev;
	const struct firmware *fw;
	int ret = request_firmware(&fw, name, dev);
	if (ret)
		return ERR_PTR(-ENOENT);
	return (void *)fw;
}