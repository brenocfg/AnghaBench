#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct allegro_dev {TYPE_1__* plat_dev; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  allegro_fw_callback ; 
 int /*<<< orphan*/  debug ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct allegro_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static int allegro_firmware_request_nowait(struct allegro_dev *dev)
{
	const char *fw = "al5e_b.fw";

	v4l2_dbg(1, debug, &dev->v4l2_dev,
		 "requesting firmware '%s'\n", fw);
	return request_firmware_nowait(THIS_MODULE, true, fw,
				       &dev->plat_dev->dev, GFP_KERNEL, dev,
				       allegro_fw_callback);
}