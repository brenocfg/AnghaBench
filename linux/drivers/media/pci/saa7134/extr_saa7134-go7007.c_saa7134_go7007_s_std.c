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
typedef  int /*<<< orphan*/  v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct saa7134_go7007 {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int saa7134_s_std_internal (struct saa7134_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct saa7134_go7007* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int saa7134_go7007_s_std(struct v4l2_subdev *sd, v4l2_std_id norm)
{
#if 0
	struct saa7134_go7007 *saa = to_state(sd);
	struct saa7134_dev *dev = saa->dev;

	return saa7134_s_std_internal(dev, NULL, norm);
#else
	return 0;
#endif
}