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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reg_w_val (struct gspca_dev*,int,int) ; 
 int /*<<< orphan*/  rev72a_init_data1 ; 
 int /*<<< orphan*/  rev72a_init_data2 ; 
 int /*<<< orphan*/  rev72a_init_sensor1 ; 
 int /*<<< orphan*/  rev72a_init_sensor2 ; 
 int /*<<< orphan*/  rev72a_reset ; 
 int /*<<< orphan*/  write_sensor_72a (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_vector (struct gspca_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sd_init_72a(struct gspca_dev *gspca_dev)
{
	gspca_dbg(gspca_dev, D_STREAM, "Chip revision: 072a\n");
	write_vector(gspca_dev, rev72a_reset);
	msleep(200);
	write_vector(gspca_dev, rev72a_init_data1);
	write_sensor_72a(gspca_dev, rev72a_init_sensor1);
	write_vector(gspca_dev, rev72a_init_data2);
	write_sensor_72a(gspca_dev, rev72a_init_sensor2);
	reg_w_val(gspca_dev, 0x8112, 0x30);
	return 0;
}