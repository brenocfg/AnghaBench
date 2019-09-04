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
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
struct fdp1_q_data {TYPE_1__ format; } ;
struct fdp1_dev {int dummy; } ;
struct fdp1_ctx {struct fdp1_q_data out_q; struct fdp1_dev* fdp1; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD1_IPC_SENSOR_CTL0 ; 
 unsigned int FD1_IPC_SENSOR_CTL0_CONST ; 
 int /*<<< orphan*/  FD1_IPC_SENSOR_CTL1 ; 
 unsigned int FD1_IPC_SENSOR_CTL1_CONST ; 
 int /*<<< orphan*/  FD1_IPC_SENSOR_CTL2 ; 
 unsigned int FD1_IPC_SENSOR_CTL2_X_SHIFT ; 
 unsigned int FD1_IPC_SENSOR_CTL2_Y_SHIFT ; 
 int /*<<< orphan*/  FD1_IPC_SENSOR_CTL3 ; 
 unsigned int FD1_IPC_SENSOR_CTL3_0_SHIFT ; 
 unsigned int FD1_IPC_SENSOR_CTL3_1_SHIFT ; 
 int /*<<< orphan*/  FD1_IPC_SENSOR_TH0 ; 
 unsigned int FD1_IPC_SENSOR_TH0_CONST ; 
 int /*<<< orphan*/  FD1_IPC_SENSOR_TH1 ; 
 unsigned int FD1_IPC_SENSOR_TH1_CONST ; 
 int /*<<< orphan*/  fdp1_write (struct fdp1_dev*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fdp1_set_ipc_sensor(struct fdp1_ctx *ctx)
{
	struct fdp1_dev *fdp1 = ctx->fdp1;
	struct fdp1_q_data *src_q_data = &ctx->out_q;
	unsigned int x0, x1;
	unsigned int hsize = src_q_data->format.width;
	unsigned int vsize = src_q_data->format.height;

	x0 = hsize / 3;
	x1 = 2 * hsize / 3;

	fdp1_write(fdp1, FD1_IPC_SENSOR_TH0_CONST, FD1_IPC_SENSOR_TH0);
	fdp1_write(fdp1, FD1_IPC_SENSOR_TH1_CONST, FD1_IPC_SENSOR_TH1);
	fdp1_write(fdp1, FD1_IPC_SENSOR_CTL0_CONST, FD1_IPC_SENSOR_CTL0);
	fdp1_write(fdp1, FD1_IPC_SENSOR_CTL1_CONST, FD1_IPC_SENSOR_CTL1);

	fdp1_write(fdp1, ((hsize - 1) << FD1_IPC_SENSOR_CTL2_X_SHIFT) |
			 ((vsize - 1) << FD1_IPC_SENSOR_CTL2_Y_SHIFT),
			 FD1_IPC_SENSOR_CTL2);

	fdp1_write(fdp1, (x0 << FD1_IPC_SENSOR_CTL3_0_SHIFT) |
			 (x1 << FD1_IPC_SENSOR_CTL3_1_SHIFT),
			 FD1_IPC_SENSOR_CTL3);
}