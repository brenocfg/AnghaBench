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
struct wil6210_priv {int dummy; } ;
struct firmware {int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int wil_brd_process (struct wil6210_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wil_dbg_fw (struct wil6210_priv*,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_err_fw (struct wil6210_priv*,char*,char const*,...) ; 
 int wil_fw_verify (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_to_dev (struct wil6210_priv*) ; 

int wil_request_board(struct wil6210_priv *wil, const char *name)
{
	int rc, dlen;
	const struct firmware *brd;

	rc = request_firmware(&brd, name, wil_to_dev(wil));
	if (rc) {
		wil_err_fw(wil, "Failed to load brd %s\n", name);
		return rc;
	}
	wil_dbg_fw(wil, "Loading <%s>, %zu bytes\n", name, brd->size);

	/* Verify the header */
	dlen = wil_fw_verify(wil, brd->data, brd->size);
	if (dlen < 0) {
		rc = dlen;
		goto out;
	}

	/* Process the data records */
	rc = wil_brd_process(wil, brd->data, dlen);

out:
	release_firmware(brd);
	if (rc)
		wil_err_fw(wil, "Loading <%s> failed, rc %d\n", name, rc);
	return rc;
}