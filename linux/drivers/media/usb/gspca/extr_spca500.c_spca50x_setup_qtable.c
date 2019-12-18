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
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int reg_w (struct gspca_dev*,unsigned int,unsigned int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int spca50x_setup_qtable(struct gspca_dev *gspca_dev,
				unsigned int request,
				unsigned int ybase,
				unsigned int cbase,
				const __u8 qtable[2][64])
{
	int i, err;

	/* loop over y components */
	for (i = 0; i < 64; i++) {
		err = reg_w(gspca_dev, request, ybase + i, qtable[0][i]);
		if (err < 0)
			return err;
	}

	/* loop over c components */
	for (i = 0; i < 64; i++) {
		err = reg_w(gspca_dev, request, cbase + i, qtable[1][i]);
		if (err < 0)
			return err;
	}
	return 0;
}