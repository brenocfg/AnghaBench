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
struct em28xx {int resources; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  em28xx_videodbg (char*,int) ; 
 int get_resource (int) ; 

__attribute__((used)) static int res_get(struct em28xx *dev, enum v4l2_buf_type f_type)
{
	int res_type = get_resource(f_type);

	/* is it free? */
	if (dev->resources & res_type) {
		/* no, someone else uses it */
		return -EBUSY;
	}

	/* it's free, grab it */
	dev->resources |= res_type;
	em28xx_videodbg("res: get %d\n", res_type);
	return 0;
}