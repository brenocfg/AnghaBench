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
struct hideep_ts {TYPE_1__* client; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_RESET_IN_PGM (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int hideep_enter_pgm (struct hideep_ts*) ; 
 int hideep_flash_firmware (struct hideep_ts*,int /*<<< orphan*/  const*,size_t) ; 
 int hideep_load_dwz (struct hideep_ts*) ; 

__attribute__((used)) static int hideep_update_firmware(struct hideep_ts *ts,
				  const __be32 *ucode, size_t ucode_len)
{
	int error, error2;

	dev_dbg(&ts->client->dev, "starting firmware update");

	/* enter program mode */
	error = hideep_enter_pgm(ts);
	if (error)
		return error;

	error = hideep_flash_firmware(ts, ucode, ucode_len);
	if (error)
		dev_err(&ts->client->dev,
			"firmware update failed: %d\n", error);
	else
		dev_dbg(&ts->client->dev, "firmware updated successfully\n");

	SW_RESET_IN_PGM(1000);

	error2 = hideep_load_dwz(ts);
	if (error2)
		dev_err(&ts->client->dev,
			"failed to load dwz after firmware update: %d\n",
			error2);

	return error ?: error2;
}