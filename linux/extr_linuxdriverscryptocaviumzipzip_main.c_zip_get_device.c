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
struct zip_device {int dummy; } ;

/* Variables and functions */
 int MAX_ZIP_DEVICES ; 
 struct zip_device** zip_dev ; 
 int /*<<< orphan*/  zip_err (char*,int) ; 

struct zip_device *zip_get_device(int node)
{
	if ((node < MAX_ZIP_DEVICES) && (node >= 0))
		return zip_dev[node];

	zip_err("ZIP device not found for node id %d\n", node);
	return NULL;
}