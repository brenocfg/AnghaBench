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
struct wmi_smbios_priv {scalar_t__ buf; int /*<<< orphan*/  req_buf_size; int /*<<< orphan*/  list; } ;
struct wmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_mutex ; 
 int /*<<< orphan*/  dell_smbios_unregister_device (int /*<<< orphan*/ *) ; 
 struct wmi_smbios_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dell_smbios_wmi_remove(struct wmi_device *wdev)
{
	struct wmi_smbios_priv *priv = dev_get_drvdata(&wdev->dev);
	int count;

	mutex_lock(&call_mutex);
	mutex_lock(&list_mutex);
	list_del(&priv->list);
	mutex_unlock(&list_mutex);
	dell_smbios_unregister_device(&wdev->dev);
	count = get_order(priv->req_buf_size);
	free_pages((unsigned long)priv->buf, count);
	mutex_unlock(&call_mutex);
	return 0;
}