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
struct inode {struct applespi_data* i_private; } ;
struct file {struct applespi_data* private_data; } ;
struct applespi_data {int tp_dim_min_x; int tp_dim_min_y; int tp_dim_max_x; int tp_dim_max_y; TYPE_2__* touchpad_input_dev; int /*<<< orphan*/  tp_dim_val; } ;
struct TYPE_3__ {int product; } ;
struct TYPE_4__ {TYPE_1__ id; } ;

/* Variables and functions */
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int,int) ; 

__attribute__((used)) static int applespi_tp_dim_open(struct inode *inode, struct file *file)
{
	struct applespi_data *applespi = inode->i_private;

	file->private_data = applespi;

	snprintf(applespi->tp_dim_val, sizeof(applespi->tp_dim_val),
		 "0x%.4x %dx%d+%u+%u\n",
		 applespi->touchpad_input_dev->id.product,
		 applespi->tp_dim_min_x, applespi->tp_dim_min_y,
		 applespi->tp_dim_max_x - applespi->tp_dim_min_x,
		 applespi->tp_dim_max_y - applespi->tp_dim_min_y);

	return nonseekable_open(inode, file);
}