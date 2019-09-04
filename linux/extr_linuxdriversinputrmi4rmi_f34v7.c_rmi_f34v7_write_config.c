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
struct TYPE_2__ {int /*<<< orphan*/  config_block_count; int /*<<< orphan*/  config_data; } ;
struct f34_data {TYPE_1__ v7; } ;

/* Variables and functions */
 int rmi_f34v7_write_f34v7_blocks (struct f34_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v7_CMD_WRITE_CONFIG ; 

__attribute__((used)) static int rmi_f34v7_write_config(struct f34_data *f34)
{
	return rmi_f34v7_write_f34v7_blocks(f34, f34->v7.config_data,
					    f34->v7.config_block_count,
					    v7_CMD_WRITE_CONFIG);
}