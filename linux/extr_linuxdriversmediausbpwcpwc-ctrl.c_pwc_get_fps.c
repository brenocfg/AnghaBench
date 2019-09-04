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
struct pwc_device {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ DEVICE_USE_CODEC1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DEVICE_USE_CODEC3 (int /*<<< orphan*/ ) ; 
 unsigned int pwc_get_fps_Kiara (struct pwc_device*,unsigned int,unsigned int) ; 
 unsigned int pwc_get_fps_Nala (struct pwc_device*,unsigned int,unsigned int) ; 
 unsigned int pwc_get_fps_Timon (struct pwc_device*,unsigned int,unsigned int) ; 

unsigned int pwc_get_fps(struct pwc_device *pdev, unsigned int index, unsigned int size)
{
	unsigned int ret;

	if (DEVICE_USE_CODEC1(pdev->type)) {
		ret = pwc_get_fps_Nala(pdev, index, size);

	} else if (DEVICE_USE_CODEC3(pdev->type)) {
		ret = pwc_get_fps_Kiara(pdev, index, size);

	} else {
		ret = pwc_get_fps_Timon(pdev, index, size);
	}

	return ret;
}