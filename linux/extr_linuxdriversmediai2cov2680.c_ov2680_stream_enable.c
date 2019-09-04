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
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2680_REG_STREAM_CTRL ; 
 int ov2680_write_reg (struct ov2680_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ov2680_stream_enable(struct ov2680_dev *sensor)
{
	return ov2680_write_reg(sensor, OV2680_REG_STREAM_CTRL, 1);
}