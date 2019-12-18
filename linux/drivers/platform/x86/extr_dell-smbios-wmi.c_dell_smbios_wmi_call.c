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
typedef  int /*<<< orphan*/  u64 ;
struct wmi_smbios_priv {int req_buf_size; TYPE_1__* buf; int /*<<< orphan*/  wdev; } ;
struct calling_interface_buffer {int dummy; } ;
struct TYPE_2__ {struct calling_interface_buffer std; int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  call_mutex ; 
 struct wmi_smbios_priv* get_first_smbios_priv () ; 
 int /*<<< orphan*/  memcpy (struct calling_interface_buffer*,struct calling_interface_buffer*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int run_smbios_call (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dell_smbios_wmi_call(struct calling_interface_buffer *buffer)
{
	struct wmi_smbios_priv *priv;
	size_t difference;
	size_t size;
	int ret;

	mutex_lock(&call_mutex);
	priv = get_first_smbios_priv();
	if (!priv) {
		ret = -ENODEV;
		goto out_wmi_call;
	}

	size = sizeof(struct calling_interface_buffer);
	difference = priv->req_buf_size - sizeof(u64) - size;

	memset(&priv->buf->ext, 0, difference);
	memcpy(&priv->buf->std, buffer, size);
	ret = run_smbios_call(priv->wdev);
	memcpy(buffer, &priv->buf->std, size);
out_wmi_call:
	mutex_unlock(&call_mutex);

	return ret;
}