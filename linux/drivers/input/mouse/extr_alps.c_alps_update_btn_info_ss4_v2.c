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
struct alps_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  dev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALPS_BUTTONPAD ; 
 scalar_t__ IS_SS4PLUS_DEV (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alps_update_btn_info_ss4_v2(unsigned char otp[][4],
				       struct alps_data *priv)
{
	unsigned char is_btnless;

	if (IS_SS4PLUS_DEV(priv->dev_id))
		is_btnless = (otp[1][0] >> 1) & 0x01;
	else
		is_btnless = (otp[1][1] >> 3) & 0x01;

	if (is_btnless)
		priv->flags |= ALPS_BUTTONPAD;

	return 0;
}