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
struct tw68_tvnorm {int id; } ;
struct tw68_dev {int width; int height; struct tw68_tvnorm const* tvnorm; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  tw68_set_tvnorm_hw (struct tw68_dev*) ; 

__attribute__((used)) static void set_tvnorm(struct tw68_dev *dev, const struct tw68_tvnorm *norm)
{
	if (norm != dev->tvnorm) {
		dev->width = 720;
		dev->height = (norm->id & V4L2_STD_525_60) ? 480 : 576;
		dev->tvnorm = norm;
		tw68_set_tvnorm_hw(dev);
	}
}