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
 int /*<<< orphan*/  reg_w_riv (struct gspca_dev*,int,int,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void setup_qtable(struct gspca_dev *gspca_dev,
			const u8 qtable[2][64])
{
	int i;

	/* loop over y components */
	for (i = 0; i < 64; i++)
		reg_w_riv(gspca_dev, 0x00, 0x2800 + i, qtable[0][i]);

	/* loop over c components */
	for (i = 0; i < 64; i++)
		reg_w_riv(gspca_dev, 0x00, 0x2840 + i, qtable[1][i]);
}