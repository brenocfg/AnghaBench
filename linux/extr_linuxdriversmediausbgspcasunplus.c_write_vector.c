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
struct cmd {int /*<<< orphan*/  val; int /*<<< orphan*/  idx; int /*<<< orphan*/  req; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_vector(struct gspca_dev *gspca_dev,
			const struct cmd *data, int ncmds)
{
	while (--ncmds >= 0) {
		reg_w_riv(gspca_dev, data->req, data->idx, data->val);
		data++;
	}
}