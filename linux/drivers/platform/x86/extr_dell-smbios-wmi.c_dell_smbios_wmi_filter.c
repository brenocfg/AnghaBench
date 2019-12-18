#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wmi_smbios_priv {int /*<<< orphan*/  req_buf_size; struct wmi_ioctl_buffer* buf; int /*<<< orphan*/  wdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * input; int /*<<< orphan*/  cmd_select; int /*<<< orphan*/  cmd_class; } ;
struct wmi_ioctl_buffer {TYPE_1__ std; } ;
struct wmi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  DELL_WMI_SMBIOS_CMD 128 
 int EFAULT ; 
 int ENODEV ; 
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  call_mutex ; 
 int /*<<< orphan*/  dell_smbios_call_filter (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wmi_smbios_priv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct wmi_ioctl_buffer*,struct wmi_ioctl_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int run_smbios_call (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long dell_smbios_wmi_filter(struct wmi_device *wdev, unsigned int cmd,
				   struct wmi_ioctl_buffer *arg)
{
	struct wmi_smbios_priv *priv;
	int ret = 0;

	switch (cmd) {
	case DELL_WMI_SMBIOS_CMD:
		mutex_lock(&call_mutex);
		priv = dev_get_drvdata(&wdev->dev);
		if (!priv) {
			ret = -ENODEV;
			goto fail_smbios_cmd;
		}
		memcpy(priv->buf, arg, priv->req_buf_size);
		if (dell_smbios_call_filter(&wdev->dev, &priv->buf->std)) {
			dev_err(&wdev->dev, "Invalid call %d/%d:%8x\n",
				priv->buf->std.cmd_class,
				priv->buf->std.cmd_select,
				priv->buf->std.input[0]);
			ret = -EFAULT;
			goto fail_smbios_cmd;
		}
		ret = run_smbios_call(priv->wdev);
		if (ret)
			goto fail_smbios_cmd;
		memcpy(arg, priv->buf, priv->req_buf_size);
fail_smbios_cmd:
		mutex_unlock(&call_mutex);
		break;
	default:
		ret = -ENOIOCTLCMD;
	}
	return ret;
}