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
struct si470x_device {int* registers; } ;
struct file {int dummy; } ;

/* Variables and functions */
 size_t SYSCONFIG1 ; 
 int SYSCONFIG1_GPIO2 ; 
 int SYSCONFIG1_RDSIEN ; 
 int SYSCONFIG1_STCIEN ; 
 int si470x_set_register (struct si470x_device*,size_t) ; 
 int si470x_start (struct si470x_device*) ; 
 scalar_t__ v4l2_fh_is_singular_file (struct file*) ; 
 int v4l2_fh_open (struct file*) ; 
 int /*<<< orphan*/  v4l2_fh_release (struct file*) ; 
 struct si470x_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int si470x_fops_open(struct file *file)
{
	struct si470x_device *radio = video_drvdata(file);
	int retval = v4l2_fh_open(file);

	if (retval)
		return retval;

	if (v4l2_fh_is_singular_file(file)) {
		/* start radio */
		retval = si470x_start(radio);
		if (retval < 0)
			goto done;

		/* enable RDS / STC interrupt */
		radio->registers[SYSCONFIG1] |= SYSCONFIG1_RDSIEN;
		radio->registers[SYSCONFIG1] |= SYSCONFIG1_STCIEN;
		radio->registers[SYSCONFIG1] &= ~SYSCONFIG1_GPIO2;
		radio->registers[SYSCONFIG1] |= 0x1 << 2;
		retval = si470x_set_register(radio, SYSCONFIG1);
	}

done:
	if (retval)
		v4l2_fh_release(file);
	return retval;
}