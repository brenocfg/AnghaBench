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
typedef  int v4l2_std_id ;
struct file {int dummy; } ;
struct dt3155_priv {int std; int width; int height; int /*<<< orphan*/  csr2; int /*<<< orphan*/  vidq; } ;

/* Variables and functions */
 int EBUSY ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VT_50HZ ; 
 int /*<<< orphan*/  VT_60HZ ; 
 scalar_t__ vb2_is_busy (int /*<<< orphan*/ *) ; 
 struct dt3155_priv* video_drvdata (struct file*) ; 

__attribute__((used)) static int dt3155_s_std(struct file *filp, void *p, v4l2_std_id norm)
{
	struct dt3155_priv *pd = video_drvdata(filp);

	if (pd->std == norm)
		return 0;
	if (vb2_is_busy(&pd->vidq))
		return -EBUSY;
	pd->std = norm;
	if (pd->std & V4L2_STD_525_60) {
		pd->csr2 = VT_60HZ;
		pd->width = 640;
		pd->height = 480;
	} else {
		pd->csr2 = VT_50HZ;
		pd->width = 768;
		pd->height = 576;
	}
	return 0;
}