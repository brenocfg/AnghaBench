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
struct vpbe_device {int /*<<< orphan*/  current_timings; } ;

/* Variables and functions */
 int /*<<< orphan*/  def_mode ; 
 int vpbe_get_std_info_by_name (struct vpbe_device*,int /*<<< orphan*/ ) ; 
 int vpbe_set_mode (struct vpbe_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vpbe_set_default_mode(struct vpbe_device *vpbe_dev)
{
	int ret;

	ret = vpbe_get_std_info_by_name(vpbe_dev, def_mode);
	if (ret)
		return ret;

	/* set the default mode in the encoder */
	return vpbe_set_mode(vpbe_dev, &vpbe_dev->current_timings);
}