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
struct rtlwifi_firmware_header {int /*<<< orphan*/  signature; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_fw_header(struct rtlwifi_firmware_header *hdr)
{
	return (le16_to_cpu(hdr->signature) & 0xfff0) == 0x5300;
}