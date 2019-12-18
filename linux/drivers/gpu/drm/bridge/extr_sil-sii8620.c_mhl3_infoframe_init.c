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
struct mhl3_infoframe {int version; int hev_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct mhl3_infoframe*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mhl3_infoframe_init(struct mhl3_infoframe *frame)
{
	memset(frame, 0, sizeof(*frame));

	frame->version = 3;
	frame->hev_format = -1;
	return 0;
}