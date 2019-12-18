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
struct wil_fw_record_file_header {scalar_t__ comment; int /*<<< orphan*/  data_len; int /*<<< orphan*/  version; } ;
struct wil6210_priv {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EINVAL ; 
 int /*<<< orphan*/  WIL_FW_VERSION_PREFIX ; 
 scalar_t__ WIL_FW_VERSION_PREFIX_LEN ; 
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (scalar_t__,int) ; 
 int /*<<< orphan*/  wil_dbg_fw (struct wil6210_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err_fw (struct wil6210_priv*,char*,size_t) ; 
 int /*<<< orphan*/  wil_hex_dump_fw (char*,int /*<<< orphan*/ ,int,int,scalar_t__,int,int) ; 

__attribute__((used)) static int fw_handle_file_header(struct wil6210_priv *wil, const void *data,
				 size_t size)
{
	const struct wil_fw_record_file_header *d = data;

	if (size != sizeof(*d)) {
		wil_err_fw(wil, "file header length incorrect: %zu\n", size);
		return -EINVAL;
	}

	wil_dbg_fw(wil, "new file, ver. %d, %i bytes\n",
		   d->version, d->data_len);
	wil_hex_dump_fw("", DUMP_PREFIX_OFFSET, 16, 1, d->comment,
			sizeof(d->comment), true);

	if (!memcmp(d->comment, WIL_FW_VERSION_PREFIX,
		    WIL_FW_VERSION_PREFIX_LEN))
		memcpy(wil->fw_version,
		       d->comment + WIL_FW_VERSION_PREFIX_LEN,
		       min(sizeof(d->comment) - WIL_FW_VERSION_PREFIX_LEN,
			   sizeof(wil->fw_version) - 1));

	return 0;
}