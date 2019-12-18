#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct TYPE_20__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct TYPE_19__ {scalar_t__ input_raw; scalar_t__ input_feeder; scalar_t__ input_yuv; int /*<<< orphan*/  vf_veceven; } ;
struct TYPE_18__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct TYPE_17__ {int /*<<< orphan*/  is_variable; } ;
struct TYPE_16__ {int /*<<< orphan*/  supported_bds_factors; } ;
struct TYPE_15__ {int /*<<< orphan*/  mode; } ;
struct TYPE_22__ {TYPE_8__ output; TYPE_7__ internal; TYPE_6__ enable; TYPE_5__ input; TYPE_4__ vf_dec; TYPE_3__ bds; TYPE_2__ pipeline; int /*<<< orphan*/  id; } ;
struct TYPE_12__ {unsigned int num_output_formats; unsigned int num_vf_formats; int /*<<< orphan*/ * vf_formats; int /*<<< orphan*/ * output_formats; TYPE_9__ sp; int /*<<< orphan*/  num_output_pins; } ;
struct TYPE_13__ {TYPE_10__ isp; } ;
struct TYPE_14__ {int /*<<< orphan*/  size; } ;
struct imgu_fw_info {scalar_t__ type; TYPE_11__ info; TYPE_1__ blob; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IMGU_FW_ISP_FIRMWARE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 

__attribute__((used)) static void imgu_css_fw_show_binary(struct device *dev, struct imgu_fw_info *bi,
				    const char *name)
{
	unsigned int i;

	dev_dbg(dev, "found firmware binary type %i size %i name %s\n",
		bi->type, bi->blob.size, name);
	if (bi->type != IMGU_FW_ISP_FIRMWARE)
		return;

	dev_dbg(dev, "    id %i mode %i bds 0x%x veceven %i/%i out_pins %i\n",
		bi->info.isp.sp.id, bi->info.isp.sp.pipeline.mode,
		bi->info.isp.sp.bds.supported_bds_factors,
		bi->info.isp.sp.enable.vf_veceven,
		bi->info.isp.sp.vf_dec.is_variable,
		bi->info.isp.num_output_pins);

	dev_dbg(dev, "    input (%i,%i)-(%i,%i) formats %s%s%s\n",
		bi->info.isp.sp.input.min_width,
		bi->info.isp.sp.input.min_height,
		bi->info.isp.sp.input.max_width,
		bi->info.isp.sp.input.max_height,
		bi->info.isp.sp.enable.input_yuv ? "yuv420 " : "",
		bi->info.isp.sp.enable.input_feeder ||
		bi->info.isp.sp.enable.input_raw ? "raw8 raw10 " : "",
		bi->info.isp.sp.enable.input_raw ? "raw12" : "");

	dev_dbg(dev, "    internal (%i,%i)\n",
		bi->info.isp.sp.internal.max_width,
		bi->info.isp.sp.internal.max_height);

	dev_dbg(dev, "    output (%i,%i)-(%i,%i) formats",
		bi->info.isp.sp.output.min_width,
		bi->info.isp.sp.output.min_height,
		bi->info.isp.sp.output.max_width,
		bi->info.isp.sp.output.max_height);
	for (i = 0; i < bi->info.isp.num_output_formats; i++)
		dev_dbg(dev, " %i", bi->info.isp.output_formats[i]);
	dev_dbg(dev, " vf");
	for (i = 0; i < bi->info.isp.num_vf_formats; i++)
		dev_dbg(dev, " %i", bi->info.isp.vf_formats[i]);
	dev_dbg(dev, "\n");
}