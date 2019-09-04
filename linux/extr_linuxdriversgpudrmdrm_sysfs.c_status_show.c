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
struct drm_connector {int /*<<< orphan*/  status; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 char* drm_get_connector_status_name (int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 struct drm_connector* to_drm_connector (struct device*) ; 

__attribute__((used)) static ssize_t status_show(struct device *device,
			   struct device_attribute *attr,
			   char *buf)
{
	struct drm_connector *connector = to_drm_connector(device);
	enum drm_connector_status status;

	status = READ_ONCE(connector->status);

	return snprintf(buf, PAGE_SIZE, "%s\n",
			drm_get_connector_status_name(status));
}