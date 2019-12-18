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
struct wil6210_priv {int /*<<< orphan*/  fw_capabilities; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WMI_FW_CAPABILITY_CHANNEL_4 ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_60ghz_channels ; 

__attribute__((used)) static int wil_num_supported_channels(struct wil6210_priv *wil)
{
	int num_channels = ARRAY_SIZE(wil_60ghz_channels);

	if (!test_bit(WMI_FW_CAPABILITY_CHANNEL_4, wil->fw_capabilities))
		num_channels--;

	return num_channels;
}