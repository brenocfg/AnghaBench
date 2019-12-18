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
typedef  unsigned char uint16_t ;
struct kone_settings {int /*<<< orphan*/  checksum; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (unsigned char) ; 

__attribute__((used)) static void kone_set_settings_checksum(struct kone_settings *settings)
{
	uint16_t checksum = 0;
	unsigned char *address = (unsigned char *)settings;
	int i;

	for (i = 0; i < sizeof(struct kone_settings) - 2; ++i, ++address)
		checksum += *address;
	settings->checksum = cpu_to_le16(checksum);
}