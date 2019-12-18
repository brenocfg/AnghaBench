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
struct gb_camera {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int gb_camera_capabilities (struct gb_camera*,char*,size_t*) ; 

__attribute__((used)) static ssize_t gb_camera_op_capabilities(void *priv, char *data, size_t len)
{
	struct gb_camera *gcam = priv;
	size_t capabilities_len = len;
	int ret;

	ret = gb_camera_capabilities(gcam, data, &capabilities_len);
	if (ret)
		return ret;

	return capabilities_len;
}