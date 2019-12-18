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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct radio_isa_card {TYPE_1__ v4l2_dev; int /*<<< orphan*/  hdl; int /*<<< orphan*/  io; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct radio_isa_card* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_isa_log_status(struct file *file, void *priv)
{
	struct radio_isa_card *isa = video_drvdata(file);

	v4l2_info(&isa->v4l2_dev, "I/O Port = 0x%03x\n", isa->io);
	v4l2_ctrl_handler_log_status(&isa->hdl, isa->v4l2_dev.name);
	return 0;
}