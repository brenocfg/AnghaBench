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
typedef  int /*<<< orphan*/  u8 ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int sn9c2028_command (struct gspca_dev*,int /*<<< orphan*/ *) ; 
 int sn9c2028_read1 (struct gspca_dev*) ; 

__attribute__((used)) static int sn9c2028_short_command(struct gspca_dev *gspca_dev, u8 *command)
{
	int err_code;

	err_code = sn9c2028_command(gspca_dev, command);
	if (err_code < 0)
		return err_code;

	err_code = sn9c2028_read1(gspca_dev);
	if (err_code < 0)
		return err_code;

	return 0;
}