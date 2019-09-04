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
struct fw_priv {size_t allocated_size; char* fw_name; scalar_t__ size; scalar_t__ data; } ;
struct device {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  enum kernel_read_file_id { ____Placeholder_kernel_read_file_id } kernel_read_file_id ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 size_t INT_MAX ; 
 int PATH_MAX ; 
 int READING_FIRMWARE ; 
 int READING_FIRMWARE_PREALLOC_BUFFER ; 
 char* __getname () ; 
 int /*<<< orphan*/  __putname (char*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*,int) ; 
 char** fw_path ; 
 int /*<<< orphan*/  fw_state_done (struct fw_priv*) ; 
 int kernel_read_file_from_path (char*,scalar_t__*,scalar_t__*,size_t,int) ; 
 int snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static int
fw_get_filesystem_firmware(struct device *device, struct fw_priv *fw_priv)
{
	loff_t size;
	int i, len;
	int rc = -ENOENT;
	char *path;
	enum kernel_read_file_id id = READING_FIRMWARE;
	size_t msize = INT_MAX;

	/* Already populated data member means we're loading into a buffer */
	if (fw_priv->data) {
		id = READING_FIRMWARE_PREALLOC_BUFFER;
		msize = fw_priv->allocated_size;
	}

	path = __getname();
	if (!path)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(fw_path); i++) {
		/* skip the unset customized path */
		if (!fw_path[i][0])
			continue;

		len = snprintf(path, PATH_MAX, "%s/%s",
			       fw_path[i], fw_priv->fw_name);
		if (len >= PATH_MAX) {
			rc = -ENAMETOOLONG;
			break;
		}

		fw_priv->size = 0;
		rc = kernel_read_file_from_path(path, &fw_priv->data, &size,
						msize, id);
		if (rc) {
			if (rc == -ENOENT)
				dev_dbg(device, "loading %s failed with error %d\n",
					 path, rc);
			else
				dev_warn(device, "loading %s failed with error %d\n",
					 path, rc);
			continue;
		}
		dev_dbg(device, "direct-loading %s\n", fw_priv->fw_name);
		fw_priv->size = size;
		fw_state_done(fw_priv);
		break;
	}
	__putname(path);

	return rc;
}