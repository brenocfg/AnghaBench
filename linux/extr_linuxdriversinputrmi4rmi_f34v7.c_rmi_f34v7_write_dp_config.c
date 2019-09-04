#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__ dp_config; } ;
struct TYPE_6__ {int config_size; int config_block_count; int block_size; TYPE_2__ img; int /*<<< orphan*/  config_data; int /*<<< orphan*/  config_area; } ;
struct f34_data {TYPE_3__ v7; } ;

/* Variables and functions */
 int rmi_f34v7_write_config (struct f34_data*) ; 
 int /*<<< orphan*/  v7_DP_CONFIG_AREA ; 

__attribute__((used)) static int rmi_f34v7_write_dp_config(struct f34_data *f34)
{
	f34->v7.config_area = v7_DP_CONFIG_AREA;
	f34->v7.config_data = f34->v7.img.dp_config.data;
	f34->v7.config_size = f34->v7.img.dp_config.size;
	f34->v7.config_block_count = f34->v7.config_size / f34->v7.block_size;

	return rmi_f34v7_write_config(f34);
}